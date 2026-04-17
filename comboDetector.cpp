#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

struct Skill {
    string name;
    vector<string> sequence;
};

class ComboDetector {
    private:
        vector<Skill> skills;
        vector<string> skillBuffer;
        int maxComboLength = 0;

        bool detectSkills(const vector<string>& buffer, const vector<string>& sequence) {
            if(buffer.size() < sequence.size())
                return false;

            auto bufferIt = buffer.end() - sequence.size();
            auto seqIt = sequence.begin();
            while(seqIt != sequence.end()) {
                if(*bufferIt != *seqIt)
                    return false;
                bufferIt++;
                seqIt++;
            }
            return true;
            
        }
    public:
        void addSkills(string name, vector<string> sequence) {
            skills.push_back({name, sequence});
            if(sequence.size() > maxComboLength)
                maxComboLength = sequence.size();
        }
        void processInput(string action) {
            cout << "收到輸入: " << action << endl;
            skillBuffer.push_back(action);

            if(skillBuffer.size() > maxComboLength)
                skillBuffer.erase(skillBuffer.begin());

            vector<Skill> triggeredSkills;
            for(const auto& skill : skills) {
                if(detectSkills(skillBuffer, skill.sequence)) {
                    triggeredSkills.push_back(skill);
                }
            }
            sort(triggeredSkills.begin(), triggeredSkills.end(), 
                 [](const Skill& a, const Skill& b) {
                     return a.sequence.size() > b.sequence.size();
                 });
            for(const auto& skill : triggeredSkills) {
                cout << "成功觸發招式：" << skill.name << endl;
            }
        }
        
};

int main() {
    ComboDetector detector;

    detector.addSkills("第一招 (A B)", {"A", "B"});
    detector.addSkills("第二招 (Down A B)", {"Down", "A", "B"});
    detector.addSkills("第三招 (Down A B A A B)", {"Down", "A", "B", "A", "A", "B"});

    cout << "--- 測試開始 ---" << endl;
    
    // 模擬輸入 
    detector.processInput("Down");
    detector.processInput("A");
    detector.processInput("B"); 
    detector.processInput("A");
    detector.processInput("A");
    detector.processInput("B");

    return 0;
}
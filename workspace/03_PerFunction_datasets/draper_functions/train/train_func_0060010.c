DelAge(const plString& name) {
    std::vector<plAgeInfo*>::iterator ai = ages.begin();
    while (ai != ages.end()) {
        if ((*ai)->getAgeName() == name) {
            plAgeInfo* age = *ai;
            delete age;
            ai = ages.erase(ai);
        } else {
            ai++;
        }
    }
}

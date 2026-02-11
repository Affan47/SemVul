operator()(const string &s1, const string &s2) const {
        return s1.substr(0, s1.find(':')) < s2.substr(0, s2.find(':'));
    }
}

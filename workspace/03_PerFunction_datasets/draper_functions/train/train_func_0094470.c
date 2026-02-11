split(vector<string>& v, const string& str, char c, bool useEmpty) {
    v.clear();
    string::const_iterator s = str.begin();
    string tmp;
    while (true) {
        string::const_iterator begin = s;
        while (*s != c && s != str.end()) { ++s; }
    tmp = string(begin, s);
    if (useEmpty || tmp.size() > 0)
            v.push_back(tmp);
        if (s == str.end()) {
            break;
        }
        if (++s == str.end()) {
        if (useEmpty)
                v.push_back("");
            break;
        }
    }
}

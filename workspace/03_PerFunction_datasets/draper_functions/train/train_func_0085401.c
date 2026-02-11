subst(const string& in, const string& out) {
    typedef vector<string>::const_iterator iter;
    vector<string> vecs1 = split(in);
    vector<string> vecs2 = split(out);
    string ret;
    string tmp;

    vector<string>::size_type i;
    vector<string>::size_type j;

    for (i = 0; i != vecs1.size(); ++i) {
        for (j = 0; j != vecs2.size(); ++j) {
            if ((vecs2[j])[0] == '#'
                && i == (vector<string>::size_type)stoi(tmp.assign(
                        vecs2[j], 1, (vecs2[i]).size() -1)) -1) {
                vecs2[j] = vecs1[i];
            }
        }
    }

    for (iter k = vecs2.begin(); k != vecs2.end(); ++k) {
        ret += *k + " ";
    }

    return ret;
}

cmp_nocase(const string &a, const string &b)
{
    string::const_iterator p = a.begin();
    string::const_iterator q = b.begin();

    while (p != a.end() && q != b.end()) {
	if (toupper(*p) != toupper(*q))
	    return ((toupper(*p) < toupper(*q)) ? -1: 1);
	++p;
	++q;
    }
    return ((b.size() == a.size()) ? 0 : (a.size() < b.size()) ? -1:1);
}

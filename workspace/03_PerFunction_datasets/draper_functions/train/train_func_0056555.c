compareTo(const mstring &s) const {
#if upstream_comp
    if (s.length() > length()) {
        return -1;
    } else if (s.length() == length()) {
        if (fCount == 0)
            return 0;
        else
            return memcmp(s.data(), data(), fCount);
    } else {
        return 1;
    }
#else
    int res=memcmp(data(), s.data(), min(s.length(), length()));
    if (s.length() == length())
       return res;
    if(res)
       return res;
    return length()-s.length();
#endif
}

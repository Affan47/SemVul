isLowerCase(const std::wstring &s)
{
    int len = s.length();
    for (int i = 0; i < len; i++) {
        char ch = s[i];
        if ((ch < L'a') || (ch > L'z'))
            return false;
    }
    return true;
}

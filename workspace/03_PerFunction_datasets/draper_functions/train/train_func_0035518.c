putUtf8(const std::wstring &string)
{
    std::string s(toUtf8(string));
    putInteger(s.length());
    putData((const unsigned char*)s.c_str(), s.length());
    return 4 + s.length();
}

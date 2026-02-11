S2U(const wxString& s,unsigned int& u)
{
    bool is_ok = true;
    u = 0;
    size_t i;
    wxChar ch;
    for (i = 0; is_ok && i < s.length();i++)
    {
        ch = s[i];
        if (ch >= _T('0') && ch <= _T('9'))
        {
            u*=10;
            u+=((unsigned int)ch) & 15;
        }
        else
            is_ok = false;
    }
    if (!is_ok)
        u = 0;
    return is_ok;
}

URLEncode(const wxString &str)
{
    wxString ret;
    wxString t;
    for (unsigned int i = 0; i < str.length(); ++i)
    {
        wxChar c = str[i];
        if (  (c >= _T('A') && c <= _T('Z'))
           || (c >= _T('a') && c <= _T('z'))
           || (c >= _T('0') && c <= _T('9'))
           || (c == _T('.'))
           || (c == _T('-'))
           || (c == _T('_')) )

            ret.Append(c);
        else if (c == _T(' '))
            ret.Append(_T('+'));
        else
        {
            t.sprintf(_T("%%%02X"), (unsigned int) c);
            ret.Append(t);
        }
    }
    return ret;
}

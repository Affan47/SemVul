getValue(const wxString& key, int& value)
{
    wxString s;
    if (!getValue(key, s))
        return false;


    long longValue;
    if (!s.ToLong(&longValue))
        return false;

    value = longValue;
    return true;
}

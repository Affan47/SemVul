getValue(const wxString& key, wxArrayString& value)
{
    wxString s;
    if (!getValue(key, s))
        return false;

    value.clear();
    wxString item;
    size_t pos = 0, sep = s.find(',');
    while (sep != wxString::npos)
    {
        item = s.substr(pos, sep - pos);
        if (!item.empty())
            value.push_back(item);
        sep = s.find(',', pos = sep + 1);
    }
    if (!(item = s.substr(pos)).empty())
        value.push_back(item);
    return true;
}

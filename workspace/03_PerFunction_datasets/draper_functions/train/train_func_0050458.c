setValue(const wxString& key, const wxArrayString& value)
{
    wxString s;
    for (wxArrayString::const_iterator it = value.begin(); it != value.end();
        it++)
    {
        if (it != value.begin())
            s += wxT(",");


        wxASSERT((*it).find(',') == wxString::npos);
        s += *it;
    }
    return setValue(key, s);
}

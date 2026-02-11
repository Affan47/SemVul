ParseGDBWatchValue(cb::shared_ptr<GDBWatch> watch, wxString const &inputValue)
{
    if(inputValue.empty())
    {
        watch->SetValue(inputValue);
        return true;
    }

    wxString value = RemoveWarnings(inputValue);


    wxString::size_type start = value.find(wxT('{'));

    if (start != wxString::npos && value[value.length() - 1] == wxT('}'))
    {

        watch->SetValue(wxEmptyString);

        int t_start = start + 1;
        bool result = ParseGDBWatchValue(watch, value, t_start, value.length() - 2);
        if (result)
        {
            if (start > 0)
            {
                wxString referenceValue = value.substr(0, start);
                referenceValue.Trim(true);
                referenceValue.Trim(false);
                if (referenceValue.EndsWith(wxT("=")))
                {
                    referenceValue.RemoveLast(1);
                    referenceValue.Trim(true);
                }
                watch->SetValue(referenceValue);
            }
            watch->RemoveMarkedChildren();
        }
        return result;
    }
    else
    {
        watch->SetValue(value);
        watch->RemoveChildren();
        return true;
    }
    return false;
}

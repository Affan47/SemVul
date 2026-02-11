GetValueAsBool( const wxSheetCoords& coords )
{
    const wxString val(GetValue(coords));
    if (val.IsEmpty() || (val == wxT("0")) ||
       (val.CmpNoCase(wxT("f")) == 0) || (val.CmpNoCase(wxT("false")) == 0))
        return false;

    return true;
}

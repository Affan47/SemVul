CanGetValueAs( const wxSheetCoords& coords,
                                  const wxString& typeName )
{
    if ((typeName == wxSHEET_VALUE_NUMBER) || (typeName == wxSHEET_VALUE_CHOICEINT))
    {
        const wxString val(GetValue(coords));
        long lval = 0;
        return val.ToLong(&lval);
    }
    else if (typeName == wxSHEET_VALUE_FLOAT)
    {
        const wxString val(GetValue(coords));
        double dval = 0.0;
        return val.ToDouble(&dval);
    }
    else if (typeName == wxSHEET_VALUE_BOOL)
    {
        const wxString val(GetValue(coords));
        return val.IsEmpty() || (val == wxT("0")) || (val == wxT("1")) ||
               (val.CmpNoCase(wxT("f")) == 0) || (val.CmpNoCase(wxT("t")) == 0) ||
               (val.CmpNoCase(wxT("false")) == 0) || (val.CmpNoCase(wxT("true")) == 0);
    }

    return typeName == wxSHEET_VALUE_STRING;
}

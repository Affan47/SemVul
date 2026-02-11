StringToValue( wxVariant& variant, const wxString& text, int WXUNUSED(argFlags) ) const
{

    bool isPrevLong = wxPGIsVariantType(variant, long);

    if ( text.length() == 0 )
    {
        variant.MakeNull();
        return true;
    }

    size_t start = 0;
    if ( text[0] == wxT('$') )
        start++;

    wxULongLong_t value64 = 0;
    wxString s = text.substr(start, text.length() - start);

    if ( wxPGStringToULongLong(s, &value64, (unsigned int)m_realBase) )
    {
        if ( value64 >= LONG_MAX )
        {
            wxULongLong* _m_value64 = &wxULongLongFromVariant(m_value);
            if ( isPrevLong || !_m_value64 || _m_value64->GetValue() != value64 )
            {
                variant = wxULongLongToVariant(value64);
                return true;
            }
        }
        else
        {
            unsigned long value32 = wxLongLong(value64).GetLo();
            if ( !isPrevLong || m_value.GetLong() != (long)value32 )
            {
                variant = (long)value32;
                return true;
            }
        }

    }
    return false;
}

DoValidation( const wxPGProperty* property, double& value, wxPGValidationInfo* pValidationInfo, int mode )
{

    double min = (double)wxINT64_MIN;
    double max = (double)wxINT64_MAX;
    wxVariant variant;
    bool minOk = false;
    bool maxOk = false;

    variant = property->GetAttribute(wxPGGlobalVars->m_strMin);
    if ( !variant.IsNull() )
    {
        wxPGVariantToDouble(variant, &min);
        minOk = true;
    }

    variant = property->GetAttribute(wxPGGlobalVars->m_strMax);
    if ( !variant.IsNull() )
    {
        wxPGVariantToDouble(variant, &max);
        maxOk = true;
    }

    if ( minOk )
    {
        if ( value < min )
        {
            if ( mode == wxPG_PROPERTY_VALIDATION_ERROR_MESSAGE )
                pValidationInfo->m_failureMessage = wxString::Format(_("Value must be %f or higher"),min);
            else if ( mode == wxPG_PROPERTY_VALIDATION_SATURATE )
                value = min;
            else
                value = max - (min - value);
            return false;
        }
    }

    if ( maxOk )
    {
        wxPGVariantToDouble(variant, &max);
        if ( value > max )
        {
            if ( mode == wxPG_PROPERTY_VALIDATION_ERROR_MESSAGE )
                pValidationInfo->m_failureMessage = wxString::Format(_("Value must be %f or less"),max);
            else if ( mode == wxPG_PROPERTY_VALIDATION_SATURATE )
                value = max;
            else
                value = min + (value - max);
            return false;
        }
    }
    return true;
}

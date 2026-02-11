GetValueFromControl( wxVariant& variant, wxPGProperty* property, wxWindow* ctrl ) const
{
    wxSimpleCheckBox* cb = (wxSimpleCheckBox*)ctrl;

    int index = cb->m_state;

    if ( index != property->GetChoiceInfo( (wxPGChoiceInfo*) NULL ) ||


         property->IsValueUnspecified()
       )
    {
        return property->ActualIntToValue(variant, index, 0);
    }
    return false;
}

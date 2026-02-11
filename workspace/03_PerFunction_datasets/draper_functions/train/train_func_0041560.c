IntToValue( wxVariant& variant, int value, int ) const
{
    bool boolValue = value ? true : false;

    if ( m_value.IsNull() || boolValue != m_value.GetBool() )
    {
        variant = wxPGVariant_Bool(boolValue);
        return true;
    }
    return false;
}

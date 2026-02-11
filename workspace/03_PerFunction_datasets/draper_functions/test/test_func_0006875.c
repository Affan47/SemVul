ResetValue()
{
    wxCHECK_RET(GetControl(), wxT("The wxSheetCellEditor must be Created first!"));
    if ( HasRange() )
        GetSpinCtrl()->SetValue((int)m_startValue);
    else
        DoResetValue(GetInitValue());
}

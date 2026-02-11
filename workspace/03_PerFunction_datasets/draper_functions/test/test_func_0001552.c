OnButtonClick( wxPropertyGrid* propGrid,
                                           wxWindow* WXUNUSED(primaryCtrl),
                                           const wxChar* cbt )
{

    PrepareValueForDialogEditing(propGrid);

    if ( !propGrid->EditorValidate() )
        return false;


    wxArrayEditorDialog* dlg = CreateEditorDialog();
#if wxUSE_VALIDATORS
    wxValidator* validator = GetValidator();
    wxPGInDialogValidator dialogValidator;
#endif

    wxPGArrayStringEditorDialog* strEdDlg = wxDynamicCast(dlg, wxPGArrayStringEditorDialog);

    if ( strEdDlg )
        strEdDlg->SetCustomButton(cbt, this);

    dlg->SetDialogValue( wxVariant(m_value) );
    dlg->Create(propGrid, wxEmptyString, m_label);

#if !wxPG_SMALL_SCREEN
    dlg->Move( propGrid->GetGoodEditorDialogPosition(this,dlg->GetSize()) );
#endif

    bool retVal;

    for (;;)
    {
        retVal = false;

        int res = dlg->ShowModal();

        if ( res == wxID_OK && dlg->IsModified() )
        {
            wxVariant value = dlg->GetDialogValue();
            if ( !value.IsNull() )
            {
                wxArrayString actualValue = value.GetArrayString();
                wxString tempStr;
                ARRSTRPROP_ARRAY_TO_STRING(tempStr, actualValue)
            #if wxUSE_VALIDATORS
                if ( dialogValidator.DoValidate( propGrid, validator, tempStr ) )
            #endif
                {
                    SetValueInEvent( actualValue );
                    retVal = true;
                    break;
                }
            }
            else
                break;
        }
        else
            break;
    }

    delete dlg;

    return retVal;
}

OnReadOnlyCheck(wxCommandEvent& event)
{
    if (m_FileNameStr.IsEmpty() || !m_FileName.FileExists())
        return;

    if (event.IsChecked())
    {

        if ( !ToggleFileReadOnly(true) )
            Manager::Get()->GetLogManager()->DebugLog(F(_T("Unable to set file '%s' read-only (probably missing access rights)."), m_FileNameStr.wx_str()));
    }
    else
    {

        if ( !ToggleFileReadOnly(false) )
            Manager::Get()->GetLogManager()->DebugLog(F(_T("Unable to set file '%s' writeable (probably missing access rights)."), m_FileNameStr.wx_str()));
    }


    XRCCTRL(*this, "chkReadOnly", wxCheckBox)->SetValue(!m_FileName.IsFileWritable());

    Manager::Get()->GetEditorManager()->CheckForExternallyModifiedFiles();
}

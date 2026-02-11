EndModal(int retVal)
{
    if (retVal == wxID_OK)
    {

        wxChoice* cmb = XRCCTRL(*this, "chcUser", wxChoice);
        m_Users.Clear();
        if (cmb->FindString(cmb->GetStringSelection(), true) == wxNOT_FOUND)
            m_Users.Add(cmb->GetStringSelection());
        for (unsigned int i = 0; i < cmb->GetCount(); ++i)
            m_Users.Add(cmb->GetString(i));
        Manager::Get()->GetConfigManager(_T("todo_list"))->Write(_T("users"), m_Users);
        Manager::Get()->GetConfigManager(_T("todo_list"))->Write(_T("last_used_user"), cmb->GetStringSelection());


        cmb = XRCCTRL(*this, "chcType", wxChoice);
        m_Types.Clear();
        if (cmb->FindString(cmb->GetStringSelection(), true) == wxNOT_FOUND)
            m_Types.Add(cmb->GetStringSelection());
        for (unsigned int i = 0; i < cmb->GetCount(); ++i)
            m_Types.Add(cmb->GetString(i));
        Manager::Get()->GetConfigManager(_T("todo_list"))->Write(_T("types"), m_Types);
        Manager::Get()->GetConfigManager(_T("todo_list"))->Write(_T("last_used_type"), cmb->GetStringSelection());

        cmb = XRCCTRL(*this, "chcStyle", wxChoice);
        Manager::Get()->GetConfigManager(_T("todo_list"))->Write(_T("last_used_style"), cmb->GetStringSelection());

        cmb = XRCCTRL(*this, "chcPosition", wxChoice);
        Manager::Get()->GetConfigManager(_T("todo_list"))->Write(_T("last_used_position"), cmb->GetStringSelection());

        wxCheckBox *checkAddDate = XRCCTRL(*this, "ID_CHECKBOX1", wxCheckBox);
        Manager::Get()->GetConfigManager(_T("todo_list"))->Write(_T("last_date_req"), checkAddDate->GetValue() );
    }

    wxScrollingDialog::EndModal(retVal);
}

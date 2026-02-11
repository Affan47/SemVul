Save()
{
    wxString path(cSets + m_CurrentSet + _T('/') + m_CurrentVar + _T('/'));
    wxString mbr(_T('#') + m_CurrentVar + _T('.'));

    m_CfgMan->DeleteSubPath(path);

    wxString s, t;
    for (unsigned int i = 0; i < builtinMembers.GetCount(); ++i)
    {
        t = ((wxTextCtrl*) FindWindow(builtinMembers[i]))->GetValue();

        if (   i == 0
            && (   (   !m_CurrentVar.IsEmpty()
                    && t.IsEmpty() )
                || t.Contains(_T('#') + m_CurrentVar) ) )
        {
            if (cbMessageBox(_("Are you sure you want to save an invalid global variable?"), _("Global variables"),
                             wxYES_NO | wxICON_QUESTION) == wxID_YES)
            {
                t.assign(_T("(invalid)"));
            }
        }

        if (t.Contains(mbr + builtinMembers[i]))
            t.assign(_T("(invalid)"));

        if (!t.IsEmpty())
            m_CfgMan->Write(path + builtinMembers[i], t);
    }

    for (unsigned int i = 0; i < 7; ++i)
    {
        s = m_Name[i]->GetValue();
        t = m_Value[i]->GetValue();

        if (t.Contains(mbr + s))
            t.assign(_T("(invalid)"));

        if (!s.IsEmpty() && !t.IsEmpty())
            m_CfgMan->Write(path + s, t);
    }
}

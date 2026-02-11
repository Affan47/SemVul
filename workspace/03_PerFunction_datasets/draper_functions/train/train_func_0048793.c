OnAutoCompAdd(cb_unused wxCommandEvent& event)
{
    wxString key = wxGetTextFromUser(_("Please enter the new keyword"), _("Add keyword"));
    if (!key.IsEmpty())
    {
        AutoCompleteMap::iterator it = m_pCurrentAutoCompMap->find(key);
        if (it != m_pCurrentAutoCompMap->end())
        {
            cbMessageBox(_("This keyword already exists!"), _("Error"), wxICON_ERROR, this);
            return;
        }
        (*m_pCurrentAutoCompMap)[key] = wxEmptyString;
        int sel = m_Keyword->Append(key);
        m_Keyword->SetSelection(sel);
        m_LastAutoCompKeyword = m_Keyword->GetStringSelection();
        AutoCompUpdate(m_LastAutoCompKeyword,m_LanguageCmb->GetValue());
        m_AutoCompTextControl->SetText(wxEmptyString);
    }
}

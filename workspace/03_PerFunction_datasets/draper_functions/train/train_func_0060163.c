DeleteVar(cb_unused wxCommandEvent& event)
{
    wxString msg;
    msg.Printf(_("Delete the global compiler variable \"%s\" from this set?"), m_CurrentVar.c_str());
    AnnoyingDialog d(_("Delete Global Variable"), msg, wxART_QUESTION);
    PlaceWindow(&d);
    if (d.ShowModal() == AnnoyingDialog::rtYES)
    {
        m_CfgMan->DeleteSubPath(cSets + m_CurrentSet + _T('/') + m_CurrentVar + _T('/'));
        m_CurrentVar = wxEmptyString;
        UpdateChoices();
        Load();
    }
}

OnDelExt(wxCommandEvent& WXUNUSED(event))
{
    if (cbMessageBox(_("Are you sure you want to remove this extension set from the list?"), _T("Confirmation"), wxYES_NO, this) == wxID_YES)
    {
        int nr = XRCCTRL(*this, "lstCommands", wxChoice)->GetSelection();
        wxChoice* cmb = XRCCTRL(*this, "lstExt", wxChoice);
        wxString extS = cmb->GetStringSelection();
        if (!extS.IsEmpty())
        {
            int ext = cmb->GetSelection();
            m_Commands[nr].erase(m_Commands[nr].begin() + ext);
            ReadExtensions(nr);
            cmb->SetSelection(0);
            m_LastExtIndex = -1;
            DisplayCommand(nr,0);
        }
        else
            cbMessageBox(_("Can't remove default commands!"), _("Error"), wxICON_ERROR, this);
    }
}

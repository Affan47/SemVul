OnClearDirClick(cb_unused wxCommandEvent& event)
{
    wxListBox* control = GetDirsListBox();
    wxArrayInt selections;
    if (!control || control->GetSelections(selections) < 1)
        return;

    if (cbMessageBox(_("Remove all directories from the list?"),
                     _("Confirmation"),
                     wxOK | wxCANCEL | wxICON_QUESTION) == wxID_OK)
    {
        control->Clear();
        m_bDirty = true;
    }
}

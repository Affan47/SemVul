OnDelete(cb_unused wxCommandEvent& event)
{
    if (m_Selection == -1)
        return;
    if (cbMessageBox(_("Are you sure you want to remove this wildcard?"), _("Confirmation"), wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT) == wxID_YES)
    {
        cbMimeType* mt = m_Array[m_Selection];
        m_Array.RemoveAt(m_Selection);
        delete mt;
    }
    FillList();
    UpdateDisplay();
}

OnMasterPathClick(cb_unused wxCommandEvent& event)
{
    wxString path = ChooseDirectory(this,
                                    _("Select directory"),
                                    XRCCTRL(*this, "txtMasterPath", wxTextCtrl)->GetValue());
    if (!path.IsEmpty())
    {
        XRCCTRL(*this, "txtMasterPath", wxTextCtrl)->SetValue(path);
        m_bDirty = true;
    }
}

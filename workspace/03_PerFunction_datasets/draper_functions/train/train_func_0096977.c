OnBrowseCommand(cb_unused wxCommandEvent& event)
{
    const wxFileName file(XRCCTRL(*this, "txtCommand", wxTextCtrl)->GetValue());
    wxString filename = wxFileSelector(_("Select executable"), file.GetPath(wxPATH_GET_VOLUME), file.GetFullName());
    if (!filename.IsEmpty())
        XRCCTRL(*this, "txtCommand", wxTextCtrl)->SetValue(filename);
}

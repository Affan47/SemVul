OnAddSymbolFile(wxCommandEvent& WXUNUSED(event))
{
    wxString file = wxFileSelector(_("Choose file to read symbols from"),
                                    _T(""),
                                    _T(""),
                                    _T(""),
                                    _("Executables and libraries|*.exe;*.dll"),
                                    wxFD_OPEN | wxFD_FILE_MUST_EXIST | compatibility::wxHideReadonly);
    if (file.IsEmpty())
        return;

    ConvertToGDBDirectory(file);

}

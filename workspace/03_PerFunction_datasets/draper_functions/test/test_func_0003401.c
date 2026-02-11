CheckColourThemeName(const wxString &name, wxWindow *parent)
{
    wxRegEx regex(wxT("^[A-Za-z][A-Za-z_0-9]*$"));
    if (regex.Matches(name))
        return true;
    else
    {
        cbMessageBox(_("You've entered invalid characters for the name of the theme. "
                       "Only alphanumeric characters and '_' are allowed! The first character should be a letter. "
                       "Please try again."),
                     _("Error"),
                     wxOK,
                     parent);
        return false;
    }
}

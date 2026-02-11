getToolbarHint(const wxString& text, int id)
{
    wxString shortcut(getShortcutText(id));
    return (shortcut.empty() ? text : text + wxT(" (") + shortcut + wxT(")"));
}

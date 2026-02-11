OnContextMenu(wxContextMenuEvent& event)
{
    SetFocus();

    CommandManager cm;
    wxMenu m;
    m.Append(wxID_UNDO, cm.getPopupMenuItemText(_("&Undo"), wxID_UNDO));
    m.Append(wxID_REDO, cm.getPopupMenuItemText(_("&Redo"), wxID_REDO));
    m.AppendSeparator();
    m.Append(wxID_CUT, cm.getPopupMenuItemText(_("Cu&t"), wxID_CUT));
    m.Append(wxID_COPY, cm.getPopupMenuItemText(_("&Copy"), wxID_COPY));
    m.Append(wxID_PASTE, cm.getPopupMenuItemText(_("&Paste"), wxID_PASTE));
    m.Append(wxID_DELETE, cm.getPopupMenuItemText(_("&Delete"), wxID_DELETE));
    m.AppendSeparator();
    m.Append(wxID_SELECTALL,
        cm.getPopupMenuItemText(_("Select &all"), wxID_SELECTALL));

    PopupMenu(&m, calcContextMenuPosition(event.GetPosition(), this));
}

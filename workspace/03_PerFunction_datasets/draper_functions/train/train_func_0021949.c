Validate(wxWindow* parent) {
    wxWindow* win = GetWindow();
    if(win == NULL)
        return false;
    wxString text;
    if(!GetWindowText(text))
        return false;
    bool valid = ((text == nonetext) ? allownone : (bool) GetRuleSetFromString(text));
    if(!valid) {
        win->SetFocus();
        wxMessageBox(wxString::Format(wxT("'%s' is not a valid rule set."), text.c_str()),
            wxT("Validation conflict"), wxOK | wxICON_EXCLAMATION, parent);
    }
    return valid;
}

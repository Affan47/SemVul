Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name )
{
    bool bRetVal = wxButton::Create(parent, id, label, pos, size, style|wxTRANSPARENT_WINDOW, validator, name);

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    SetBackgroundColour(parent->GetBackgroundColour());
    SetForegroundColour(parent->GetForegroundColour());

    return bRetVal;
}

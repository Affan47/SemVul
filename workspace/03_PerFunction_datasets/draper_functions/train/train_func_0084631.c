OnUpdateUI(cb_unused wxUpdateUIEvent& event)
{
    const wxString name = XRCCTRL(*this, "txtName", wxTextCtrl)->GetValue();
    const wxString command = XRCCTRL(*this, "txtCommand", wxTextCtrl)->GetValue();
    bool en = !name.IsEmpty() && !command.IsEmpty();
    XRCCTRL(*this, "wxID_OK", wxButton)->Enable(en);
}

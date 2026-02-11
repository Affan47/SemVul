OnUpdateUI(cb_unused wxUpdateUIEvent& event)
{
    XRCCTRL(*this, "wxID_OK", wxButton)->Enable(!XRCCTRL(*this, "txtKey", wxTextCtrl)->GetValue().IsEmpty());
}

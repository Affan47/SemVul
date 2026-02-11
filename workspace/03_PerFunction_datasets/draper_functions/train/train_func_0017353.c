OnUpdateUI(cb_unused wxUpdateUIEvent& event)
{
    bool en = XRCCTRL(*this, "chkEnabled", wxCheckBox)->IsChecked();
    XRCCTRL(*this, "chkIgnore", wxCheckBox)->Enable(en && !XRCCTRL(*this, "chkExpr", wxCheckBox)->IsChecked());
    XRCCTRL(*this, "spnIgnoreCount", wxSpinCtrl)->Enable(en && XRCCTRL(*this, "chkIgnore", wxCheckBox)->IsChecked());
    XRCCTRL(*this, "chkExpr", wxCheckBox)->Enable(en && !XRCCTRL(*this, "chkIgnore", wxCheckBox)->IsChecked());
    XRCCTRL(*this, "txtExpr", wxTextCtrl)->Enable(en && XRCCTRL(*this, "chkExpr", wxCheckBox)->IsChecked());
}

OnMousewheelModifier(cb_unused wxKeyEvent& event)
{
    wxString keys;

    if (wxGetKeyState(WXK_SHIFT))
        keys += keys.IsEmpty()?wxT("Shift"):wxT("+Shift");

    if (wxGetKeyState(WXK_CONTROL))
        keys += keys.IsEmpty()?wxT("Ctrl"):wxT("+Ctrl");

#if defined(__WXMAC__) || defined(__WXCOCOA__)
    if (wxGetKeyState(WXK_COMMAND))
        keys += keys.IsEmpty()?wxT("XCtrl"):wxT("+XCtrl");
#endif

    if (wxGetKeyState(WXK_ALT))
        keys += keys.IsEmpty()?wxT("Alt"):wxT("+Alt");

    if (!keys.IsEmpty())
        XRCCTRL(*this, "txtMousewheelModifier", wxTextCtrl)->SetValue(keys);
}

ProcessValueTooltip(CodeBlocksEvent& event)
{
    event.Skip();
    if (cbDebuggerCommonConfig::GetFlag(cbDebuggerCommonConfig::RequireCtrlForTooltips))
    {
        if (!wxGetKeyState(WXK_CONTROL))
            return;
    }

    if (Manager::Get()->GetDebuggerManager()->GetInterfaceFactory()->IsValueTooltipShown())
        return;

    if (!ShowValueTooltip(event.GetInt()))
        return;

    EditorBase* base = event.GetEditor();
    cbEditor* ed = base && base->IsBuiltinEditor() ? static_cast<cbEditor*>(base) : nullptr;
    if (!ed)
        return;

    if (ed->IsContextMenuOpened())
        return;


    if (ed->GetControl()->CallTipActive())
        ed->GetControl()->CallTipCancel();

    wxPoint pt;
    pt.x = event.GetX();
    pt.y = event.GetY();

    const wxString &token = GetEditorWordAtCaret(&pt);
    if (!token.empty())
    {
        pt = ed->GetControl()->ClientToScreen(pt);
        OnValueTooltip(token, wxRect(pt.x - 5, pt.y, 10, 10));
    }
}

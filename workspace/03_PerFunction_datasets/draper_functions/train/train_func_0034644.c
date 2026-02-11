NotifyFocus(bool focus)
{
    wxScintillaEvent evt(focus ? wxEVT_SCI_SETFOCUS : wxEVT_SCI_KILLFOCUS, GetId());
    evt.SetEventObject(this);
    GetEventHandler()->ProcessEvent(evt);
}

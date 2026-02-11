sendGuiEvent(EGUI_EVENT_TYPE type)
{
	if ( Parent )
	{
        SEvent e;
        e.EventType = EET_GUI_EVENT;
        e.GUIEvent.Caller = this;
        e.GUIEvent.Element = 0;
        e.GUIEvent.EventType = type;

        Parent->OnEvent(e);
	}
}

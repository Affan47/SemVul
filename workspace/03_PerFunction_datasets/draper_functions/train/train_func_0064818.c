OnPostRender(u32 timeMs)
{
	if (Dragging && !DraggedBySlider && TrayClick && timeMs > LastChange + 200)
	{
		LastChange = timeMs;

		const s32 oldPos = Pos;

		if (DesiredPos >= Pos + LargeStep)
			setPos(Pos + LargeStep);
		else
		if (DesiredPos <= Pos - LargeStep)
			setPos(Pos - LargeStep);
		else
		if (DesiredPos >= Pos - LargeStep && DesiredPos <= Pos + LargeStep)
			setPos(DesiredPos);

		if (Pos != oldPos && Parent)
		{
			SEvent newEvent;
			newEvent.EventType = EET_GUI_EVENT;
			newEvent.GUIEvent.Caller = this;
			newEvent.GUIEvent.Element = 0;
			newEvent.GUIEvent.EventType = EGET_SCROLL_BAR_CHANGED;
			Parent->OnEvent(newEvent);
		}
	}

}

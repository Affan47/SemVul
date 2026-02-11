OnEvent(const SEvent& event)
{
	if (IsEnabled)
	{

		switch(event.EventType)
		{
		case EET_GUI_EVENT:
			if (event.GUIEvent.EventType == EGET_ELEMENT_FOCUS_LOST)
			{
				if (event.GUIEvent.Caller == this)
				{
					MouseMarking = false;
					setTextMarkers(0,0);
				}
			}
			break;
		case EET_KEY_INPUT_EVENT:
			if (processKey(event))
				return true;
			break;
		case EET_MOUSE_INPUT_EVENT:
			if (processMouse(event))
				return true;
			break;
		default:
			break;
		}
	}

	return IGUIElement::OnEvent(event);
}

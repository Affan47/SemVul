OnEvent(const SEvent &event)
	{
		if ( event.EventType != EET_GUI_EVENT )
			return false;

		if ( event.GUIEvent.Caller == ComboTexture && event.GUIEvent.EventType == gui::EGET_COMBO_BOX_CHANGED )
		{
			DirtyFlag = true;
		}

		return false;
	}

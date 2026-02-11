gb_raise_MouseEvent(gControl *sender, int type)
{
	CWIDGET *ob = GetObject(sender);
	bool ret = false;

	if (!ob) return false;

	switch(type)
	{
		case gEvent_MouseDrag:
			if (gMouse::button() && GB.CanRaise(ob, EVENT_MouseDrag))
				ret = GB.Raise(ob, EVENT_MouseDrag, 0);
			break;

		case gEvent_MouseMenu:

			for(;;)
			{
				if (GB.CanRaise(ob, EVENT_Menu))
				{
					GB.Raise(ob, EVENT_Menu, 0);
					return true;
				}

				if (ob->popup)
				{
					gMainWindow *window = sender->window();
					gMenu *menu = gMenu::findFromName(window, ob->popup);
					if (menu)
						menu->popup();
					return true;
				}

				if (sender->isTopLevel())
					break;

				sender = sender->parent();
				ob = GetObject(sender);
			}

			break;

		default:
			ret = GB.Raise(ob, to_gambas_event(type), 0);

	}

	return ret;
}

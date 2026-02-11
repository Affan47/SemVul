recursive_change_colorset(
	container_info *c, int colorset, XEvent *Event)
{
	int button;
	button_info *ub, *b;
	button_info *tmpb;

	button = -1;
	ub = UberButton;
	while (NextButton(&ub, &b, &button, 1))
	{
		Bool redraw = False;

		tmpb = b;

		while (tmpb->parent != NULL && !redraw)
		{
			if (buttonColorset(tmpb) == colorset)
			{
				redraw = True;
			}
			tmpb = tmpb->parent;
		}
		if (!redraw)
		{
			continue;
		}
		if (b->flags.b_Swallow)
		{

			if (buttonSwallowCount(b) == 3 && b->IconWin != None)
			{
				RedrawButton(b, DRAW_ALL, NULL);
				if (b->flags.b_Colorset &&
				    !(b->swallow&b_FvwmModule))
				{
					change_swallowed_window_colorset(
						b, True);
				}
			}
		}
		else
		{
			RedrawButton(b, DRAW_ALL, NULL);
		}
	}

	return;
}

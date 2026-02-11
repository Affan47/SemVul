GNOME_HandlePropRequest(
	const exec_context_t *exc, unsigned int propm, unsigned int prop)
{
	Atom atype;
	Atom a;
	int aformat;
	FvwmWindow *fwin;
	unsigned char *indi;
	unsigned long nitems, bytes_remain, oldprop;
	indi = (unsigned char *)&oldprop;
	DBUG("HandleGnomePropRequest","Routine Entered");

	a = XInternAtom(dpy, XA_WIN_STATE, False);

	for (fwin = Scr.FvwmRoot.next; fwin; fwin = fwin->next)
	{
		if (FW_W(fwin) == exc->w.w)
		{
			break;
		}
	}


#ifdef FVWM_DEBUG_MSGS
	fvwm_msg(
		DBG, "HandleGnomePropRequest", "window is %d", (int)FW_W(fwin));
#endif
	if (fwin == NULL)
	{
		return;
	}
	if (DO_IGNORE_GNOME_HINTS(fwin))
	{
		return;
	}

#ifdef FVWM_DEBUG_MSGS
	fvwm_msg(DBG, "HandleGnomePropRequest", "prop req is %d", prop);
	fvwm_msg(DBG, "HandleGnomePropRequest", "propm req is %d", propm);
#endif
	XGetWindowProperty(dpy, FW_W(fwin), a, 0L, 3L, False, a,
			   &atype, &aformat, &nitems, &bytes_remain, &indi);
	oldprop &= ~(propm);
	oldprop |= (propm & prop);
#ifdef FVWM_DEBUG_MSGS
	fvwm_msg(
		DBG, "HandleGnomePropRequest", "oldprop req is %d",
		(int)oldprop);
#endif
	XChangeProperty(
		dpy, FW_W(fwin), a, XA_CARDINAL, 32, PropModeReplace,
		(unsigned char *)&oldprop, 1);


	if (propm & WIN_STATE_STICKY)
	{
		if (prop & WIN_STATE_STICKY)
		{
			SET_STICKY_ACROSS_PAGES(fwin, 1);
			SET_STICKY_ACROSS_DESKS(fwin, 1);
		}
		else
		{
			SET_STICKY_ACROSS_PAGES(fwin, 0);
			SET_STICKY_ACROSS_DESKS(fwin, 0);
		}
		border_draw_decorations(
			fwin, PART_TITLE, (Scr.Hilite==fwin), True, CLEAR_ALL,
			NULL, NULL);
	}


	if (propm & WIN_STATE_SHADED)
	{
		if (prop & WIN_STATE_SHADED)
		{

			execute_function_override_window(
				NULL, exc, "WindowShade True", 0, fwin);
		}
		else
		{

			execute_function_override_window(
				NULL, exc, "WindowShade False", 0, fwin);
		}
	}

	return;
}

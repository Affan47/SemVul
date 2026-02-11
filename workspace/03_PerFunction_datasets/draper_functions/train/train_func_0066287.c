frame_init(void)
{
	XSetWindowAttributes xswa;
	unsigned long valuemask;
	int i;

	xswa.override_redirect = True;
	xswa.backing_store = NotUseful;
	xswa.save_under = False;
	xswa.win_gravity = UnmapGravity;
	xswa.background_pixmap = None;
	valuemask = CWOverrideRedirect | CWSaveUnder | CWBackingStore |
		CWBackPixmap | CWWinGravity;
	hide_wins.parent = Scr.Root;
	for (i = 0; i < 4; i++)
	{
		hide_wins.w[i] = XCreateWindow(
			dpy, Scr.Root, -1, -1, 1, 1, 0, CopyFromParent,
			InputOutput, CopyFromParent, valuemask, &xswa);
		if (hide_wins.w[i] == None)
		{
			fvwm_msg(ERR, "frame_init",
				 "Could not create internal windows. Exiting");
			MyXUngrabServer(dpy);
			exit(1);
		}
	}

	return;
}

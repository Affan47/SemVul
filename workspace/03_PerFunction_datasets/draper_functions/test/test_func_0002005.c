do_menu (MenuRoot *menu,
		     Window w)
{
    int x = Event.xbutton.x_root;
    int y = Event.xbutton.y_root;
    Bool center;

    if (!Scr->NoGrabServer)
	XGrabServer(dpy);
    if (w) {
	int h = Scr->TBInfo.width - Scr->TBInfo.border;
	Window child;

	(void) XTranslateCoordinates (dpy, w, Scr->Root, 0, h, &x, &y, &child);
	center = False;
    } else {
	center = True;
    }
    if (PopUpMenu (menu, x, y, center)) {
	UpdateMenu();
    } else {
	XBell (dpy, 0);
    }
}

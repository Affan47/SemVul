HandleMotionNotify(void)
{
    if (ResizeWindow != (Window) 0)
    {
	XQueryPointer( dpy, Event.xany.window,
	    &(Event.xmotion.root), &JunkChild,
	    &(Event.xmotion.x_root), &(Event.xmotion.y_root),
	    &(Event.xmotion.x), &(Event.xmotion.y),
	    &JunkMask);

	if (Scr->Root != Scr->RealRoot) FixRootEvent (&Event);


	if (abs (Event.xmotion.x - ResizeOrigX) >= Scr->MoveDelta
	    || abs (Event.xmotion.y - ResizeOrigY) >= Scr->MoveDelta)
	  WindowMoved = TRUE;

	XFindContext(dpy, ResizeWindow, TwmContext, (XPointer *)&Tmp_win);
	if (Tmp_win && Tmp_win->winbox) {
	    XTranslateCoordinates (dpy, Scr->Root, Tmp_win->winbox->window,
		Event.xmotion.x_root, Event.xmotion.y_root,
		&(Event.xmotion.x_root), &(Event.xmotion.y_root), &JunkChild);
	}
	DoResize(Event.xmotion.x_root, Event.xmotion.y_root, Tmp_win);
    }
    else
    if (Scr->BorderCursors && Tmp_win && Event.xany.window == Tmp_win->frame) {
	SetBorderCursor (Tmp_win, Event.xmotion.x, Event.xmotion.y);
    }
}

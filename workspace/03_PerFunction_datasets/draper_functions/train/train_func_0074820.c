setFocus(bool focus)
{
	has_focus=focus;

	if (has_title)
	{
		if(has_focus)
		{
			XSetWindowBackground(dpy, title, wm->getBGColor().pixel);
			XSetWindowBorder(dpy, frame, wm->getFocusedBorderColor().pixel);
		}
		else  {
			XSetWindowBackground(dpy, title, wm->getFCColor().pixel);
			XSetWindowBorder(dpy, frame, wm->getUnFocusedBorderColor().pixel);
		}

		XClearWindow(dpy, title);
		redraw();
	}
}

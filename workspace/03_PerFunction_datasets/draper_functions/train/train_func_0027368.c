clientwin_move(ClientWin *cw, float f, int x, int y)
{

	int border = 0;
	XSetWindowBorderWidth(cw->mainwin->dpy, cw->mini.window, border);

	cw->factor = f;
	cw->mini.x = x + (int)cw->x * f;
	cw->mini.y = y + (int)cw->y * f;
	if(cw->mainwin->lazy_trans)
	{
		cw->mini.x += cw->mainwin->x;
		cw->mini.y += cw->mainwin->y;
	}
	cw->mini.width = MAX(1, (int)cw->client.width * f);
	cw->mini.height = MAX(1, (int)cw->client.height * f);
	XMoveResizeWindow(cw->mainwin->dpy, cw->mini.window, cw->mini.x - border, cw->mini.y - border, cw->mini.width, cw->mini.height);

	if(cw->pixmap)
		XFreePixmap(cw->mainwin->dpy, cw->pixmap);

	if(cw->destination)
		XRenderFreePicture(cw->mainwin->dpy, cw->destination);

	cw->pixmap = XCreatePixmap(cw->mainwin->dpy, cw->mini.window, cw->mini.width, cw->mini.height, cw->mainwin->depth);
	XSetWindowBackgroundPixmap(cw->mainwin->dpy, cw->mini.window, cw->pixmap);

	cw->destination = XRenderCreatePicture(cw->mainwin->dpy, cw->pixmap, cw->mini.format, 0, 0);
}

xdndCursorInit(Display *display, Window rw)
{
  Pixmap ip,mp;
  XdndCursor *cursorPtr;
  XColor black, white;


  black.pixel = BlackPixel(display, DefaultScreen (display));
  XQueryColor(display, DefaultColormap (display, DefaultScreen(display)),
	      &black);
  white.pixel = WhitePixel(display, DefaultScreen (display));
  XQueryColor(display, DefaultColormap (display, DefaultScreen(display)),
	      &white);


  for (cursorPtr = &xdndCursors[0];cursorPtr->w != 0;cursorPtr++) {
    ip = XCreateBitmapFromData(display, rw, (char *) cursorPtr->imageData,
			       cursorPtr->w, cursorPtr->h);
    mp = XCreateBitmapFromData(display, rw, (char *) cursorPtr->maskData,
			       cursorPtr->w, cursorPtr->h);
    cursorPtr->cursor = XCreatePixmapCursor (display, ip, mp, &black, &white,
					  cursorPtr->x, cursorPtr->y);
    XFreePixmap (display, ip);
    XFreePixmap (display, mp);
    cursorPtr->action = XInternAtom (display, cursorPtr->actionStr, False);
  }
}

doFlash(bool yes)
{
	flashing_ = yes;
	if (parentWidget_->window() != parentWidget_)
		return;

#ifdef Q_WS_WIN
	FLASHWINFO fwi;
	fwi.cbSize = sizeof(fwi);
	fwi.hwnd = parentWidget_->winId();
	if (yes) {
		fwi.dwFlags = FLASHW_ALL | FLASHW_TIMER;
		fwi.dwTimeout = 0;
		fwi.uCount = 5;
	}
	else {
		fwi.dwFlags = FLASHW_STOP;
		fwi.uCount = 0;
	}
	FlashWindowEx(&fwi);

#elif defined( Q_WS_X11 )
	static Atom demandsAttention = None;
	static Atom wmState = None;


    Display *xdisplay = QX11Info::display();
    Window rootwin = QX11Info::appRootWindow();

	if (demandsAttention == None)
    	demandsAttention = XInternAtom(xdisplay, "_NET_WM_STATE_DEMANDS_ATTENTION", true);
	if (wmState == None)
		wmState = XInternAtom(xdisplay, "_NET_WM_STATE", true);

    XEvent e;
    e.xclient.type = ClientMessage;
    e.xclient.message_type = wmState;
    e.xclient.display = xdisplay;
    e.xclient.window = parentWidget_->winId();
    e.xclient.format = 32;
    e.xclient.data.l[1] = demandsAttention;
    e.xclient.data.l[2] = 0l;
    e.xclient.data.l[3] = 0l;
    e.xclient.data.l[4] = 0l;

    if (yes) {
        e.xclient.data.l[0] = 1;
    }
    else {
        e.xclient.data.l[0] = 0;
    }
    XSendEvent(xdisplay, rootwin, False, (SubstructureRedirectMask | SubstructureNotifyMask), &e);

#else
	Q_UNUSED(yes)
#endif
}

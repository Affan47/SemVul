Realize(Widget gw, XtValueMask *mask,
		    XSetWindowAttributes *attributes)
{
    CloseShellWidget	w = (CloseShellWidget)gw;
    Display		*disp = XtDisplay(w);
    Atom		wm_delete_window;

    if (w->close_shell.cursor != None) {
	*mask |= CWCursor;
	attributes->cursor = w->close_shell.cursor;
    }

    transientShellWidgetClass->core_class.realize((Widget)w, mask, attributes);

    wm_delete_window = intern_atom(disp, "WM_DELETE_WINDOW");
    XSetWMProtocols(disp, XtWindow(w), &wm_delete_window, 1);
}

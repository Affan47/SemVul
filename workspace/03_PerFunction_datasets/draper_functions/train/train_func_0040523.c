flush_expose(Window w) {

	XEvent 		dummy;
	int			i=0;

	while (XCheckTypedWindowEvent(display, w, Expose, &dummy))
		i++;

	return i;
}

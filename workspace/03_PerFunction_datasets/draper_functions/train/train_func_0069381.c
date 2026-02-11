clean_up(void) {
	int i;

	free_event_list();
#ifndef DZEN_XFT
	if(dzen.font.set)
		XFreeFontSet(dzen.dpy, dzen.font.set);
	else
		XFreeFont(dzen.dpy, dzen.font.xfont);
#endif

	XFreePixmap(dzen.dpy, dzen.title_win.drawable);
	if(dzen.slave_win.max_lines) {
		for(i=0; i < dzen.slave_win.max_lines; i++) {
			XFreePixmap(dzen.dpy, dzen.slave_win.drawable[i]);
			XDestroyWindow(dzen.dpy, dzen.slave_win.line[i]);
		}
		free(dzen.slave_win.line);
		XDestroyWindow(dzen.dpy, dzen.slave_win.win);
	}
	XFreeGC(dzen.dpy, dzen.gc);
	XFreeGC(dzen.dpy, dzen.rgc);
	XFreeGC(dzen.dpy, dzen.tgc);
	XDestroyWindow(dzen.dpy, dzen.title_win.win);
	XCloseDisplay(dzen.dpy);
}

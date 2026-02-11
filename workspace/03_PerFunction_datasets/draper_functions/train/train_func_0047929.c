panel_applet_request_focus (PanelApplet	 *applet,
			    guint32	  timestamp)
{
	GdkScreen  *screen;
	GdkWindow  *root;
	GdkDisplay *display;
	Display	   *xdisplay;
	Window	    dock_xwindow;
	Window	    xroot;
	XEvent	    xev;

	g_return_if_fail (PANEL_IS_APPLET (applet));

	screen	= gtk_widget_get_screen (GTK_WIDGET (applet));
	root	= gdk_screen_get_root_window (screen);
	display = gdk_screen_get_display (screen);

	xdisplay = GDK_DISPLAY_XDISPLAY (display);
	xroot	 = GDK_WINDOW_XID (root);

	panel_applet_init_atoms (xdisplay);

	dock_xwindow = panel_applet_find_toplevel_dock_window (applet, xdisplay);
	if (dock_xwindow == None)
		return;

	xev.xclient.type	 = ClientMessage;
	xev.xclient.serial	 = 0;
	xev.xclient.send_event	 = True;
	xev.xclient.window	 = dock_xwindow;
	xev.xclient.message_type = _net_active_window;
	xev.xclient.format	 = 32;
	xev.xclient.data.l[0]	 = 1;
	xev.xclient.data.l[1]	 = timestamp;
	xev.xclient.data.l[2]	 = None;
	xev.xclient.data.l[3]	 = 0;
	xev.xclient.data.l[4]	 = 0;

	XSendEvent (xdisplay,
		    xroot, False,
		    SubstructureRedirectMask | SubstructureNotifyMask,
		    &xev);
}

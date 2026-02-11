gkrellm_winop_update_struts(void)
	{
	gulong	struts[12] = { 0, };
	Display	*display;
	Window	window;
	gint	width;
	gint	height;

	if (!_GK.is_dock_type)
		return;

	display = GDK_WINDOW_XDISPLAY(gkrellm_get_top_window()->window);
	window  = GDK_WINDOW_XWINDOW(gkrellm_get_top_window()->window);

	if (net_wm_strut_partial == None)
		{
		net_wm_strut_partial
				= XInternAtom(display, "_NET_WM_STRUT_PARTIAL", False);
		}
	if (net_wm_strut == None)
		{
		net_wm_strut = XInternAtom(display, "_NET_WM_STRUT", False);
		}

	gtk_window_get_size(GTK_WINDOW(gkrellm_get_top_window()), &width, &height);

	if (_GK.x_position == 0)
		{
		struts[STRUT_LEFT] = width;
		struts[STRUT_LEFT_START] = _GK.y_position;
		struts[STRUT_LEFT_END] = _GK.y_position + height;
		}
	else if (_GK.x_position == _GK.w_display - width)
		{
		struts[STRUT_RIGHT] = width;
		struts[STRUT_RIGHT_START] = _GK.y_position;
		struts[STRUT_RIGHT_END] = _GK.y_position + height;
		}

	gdk_error_trap_push();
	XChangeProperty (display, window, net_wm_strut,
					XA_CARDINAL, 32, PropModeReplace,
					(guchar *) &struts, 4);
	XChangeProperty (display, window, net_wm_strut_partial,
					XA_CARDINAL, 32, PropModeReplace,
					(guchar *) &struts, 12);
	gdk_error_trap_pop();
	}

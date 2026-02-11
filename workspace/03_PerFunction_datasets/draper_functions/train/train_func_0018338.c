accessx_status_applet_xkb_select (AccessxStatusApplet *sapplet)
{
	int opcode_rtn, error_rtn;
	gboolean retval = FALSE;
	Display *display = NULL;
        GdkWindow *window;

        window = gtk_widget_get_window (GTK_WIDGET (sapplet->applet));
	g_assert (sapplet && sapplet->applet && window);
	display = GDK_WINDOW_XDISPLAY (window);
	g_assert (display);
	retval = XkbQueryExtension (display, &opcode_rtn, &xkb_base_event_type,
				    &error_rtn, NULL, NULL);
	if (retval) {
		retval = XkbSelectEvents (display, XkbUseCoreKbd,
					  XkbAllEventsMask,
					  XkbAllEventsMask);
		sapplet->xkb = accessx_status_applet_get_xkb_desc (sapplet);
	} else {
		sapplet->error_type = ACCESSX_STATUS_ERROR_XKB_DISABLED;
	}

	return retval;
}

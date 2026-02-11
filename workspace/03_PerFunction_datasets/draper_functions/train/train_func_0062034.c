accessx_status_applet_slowkeys_image (AccessxStatusApplet *sapplet,
				      XkbAccessXNotifyEvent *event)
{
	GdkPixbuf *ret_pixbuf;
	GdkWindow *window;
	gboolean is_idle = TRUE;
	gchar *stock_id = SLOWKEYS_IDLE_ICON;
	GtkStyle *style = gtk_widget_get_style (GTK_WIDGET (sapplet->applet));
	GdkColor bg = style->bg[GTK_STATE_NORMAL];

	if (event != NULL) {
		is_idle = FALSE;
		switch (event->detail) {
		case XkbAXN_SKPress:
			stock_id = ACCESSX_BASE_ICON;
			if (_sk_timeout) {
				g_source_remove (_sk_timeout);
				_sk_timeout = 0;
			}
			break;
		case XkbAXN_SKAccept:
			stock_id = ACCESSX_ACCEPT_BASE;
			gdk_color_parse ("#009900", &bg);
			break;
		case XkbAXN_SKReject:
			stock_id = ACCESSX_REJECT_BASE;
			gdk_color_parse ("#990000", &bg);
			_sk_timeout = g_timeout_add_full (G_PRIORITY_HIGH_IDLE,
							  MAX (event->sk_delay, 150),
							  timer_reset_slowkeys_image,
							  sapplet->slowfoo, NULL);
			break;
		case XkbAXN_SKRelease:
		default:
			stock_id = SLOWKEYS_IDLE_ICON;
			is_idle = TRUE;
			break;
		}
	}
	ret_pixbuf = gtk_widget_render_icon (GTK_WIDGET (sapplet->applet),
					     stock_id,
					     icon_size_spec,
					     NULL);
	if (!is_idle) {
		GdkPixbuf *glyph_pixbuf, *tmp_pixbuf;
		GdkColor  fg;
		gchar * glyphstring = N_("a");
		tmp_pixbuf = ret_pixbuf;
		ret_pixbuf = gdk_pixbuf_copy (tmp_pixbuf);
		g_object_unref (tmp_pixbuf);

		window = gtk_widget_get_window (GTK_WIDGET (sapplet->applet));

		if (event && window) {
			KeySym keysym = XKeycodeToKeysym (
				GDK_WINDOW_XDISPLAY (window),
				event->keycode,
				0);
			glyphstring = XKeysymToString (keysym);
			if ((!g_utf8_validate (glyphstring, -1, NULL)) ||
			    (g_utf8_strlen (glyphstring, -1) > 1))
				glyphstring = "";
		}
		fg = style->fg[gtk_widget_get_state (GTK_WIDGET (sapplet->applet))];
		glyph_pixbuf = accessx_status_applet_get_glyph_pixbuf (sapplet,
								       GTK_WIDGET (sapplet->applet),
								       ret_pixbuf,
								       &fg,
								       &bg,
								       glyphstring);
		gdk_pixbuf_composite (glyph_pixbuf, ret_pixbuf, 0, 0,
				      gdk_pixbuf_get_width (glyph_pixbuf),
				      gdk_pixbuf_get_height (glyph_pixbuf),
				      0., 0., 1.0, 1.0, GDK_INTERP_NEAREST, 255);
		g_object_unref (glyph_pixbuf);
	}
	return ret_pixbuf;
}

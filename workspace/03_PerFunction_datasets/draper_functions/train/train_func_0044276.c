gtkutil_esc_destroy (GtkWidget * win, GdkEventKey * key, gpointer userdata)
{
	GtkWidget *wid;


	if (!gtk_widget_is_toplevel (win))
	{
		if (gdk_window_get_type_hint (gtk_widget_get_window (win)) == GDK_WINDOW_TYPE_HINT_DIALOG)
			wid = gtk_widget_get_parent (win);
		else
			return FALSE;
	}
	else
		wid = win;

	if (key->keyval == GDK_Escape)
		gtk_widget_destroy (wid);

	return FALSE;
}

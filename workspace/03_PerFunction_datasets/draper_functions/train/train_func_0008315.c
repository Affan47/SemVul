brasero_io_xid_for_metadata (gpointer user_data)
{
	BraseroIOPrivate *priv;

	priv = BRASERO_IO_PRIVATE (user_data);
	if (priv->win_callback) {
		int xid;
		GtkWindow *parent;

		parent = priv->win_callback (priv->win_user_data);
		xid = gdk_x11_window_get_xid (gtk_widget_get_window(GTK_WIDGET (parent)));
		return xid;
	}

	return 0;
}

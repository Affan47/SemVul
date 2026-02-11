brasero_player_bacon_draw (GtkWidget *widget, cairo_t *cr)
{
	BraseroPlayerBacon *bacon;
	GdkWindow *window;

	g_return_val_if_fail (widget != NULL, FALSE);

	bacon = BRASERO_PLAYER_BACON (widget);

	window = gtk_widget_get_window (widget);
	if (window)
		bacon->priv->xid = gdk_x11_window_get_xid (window);

	if (bacon->priv->xoverlay
	&&  GST_IS_VIDEO_OVERLAY (bacon->priv->xoverlay)
	&&  bacon->priv->state >= GST_STATE_PAUSED)
		gst_video_overlay_expose (bacon->priv->xoverlay);
	else if (window)
		gtk_widget_queue_draw (GTK_WIDGET (widget));

	return TRUE;
}

seek_started (GtkRange *range,
	      GdkEventButton *event,
	      GSRWindow *window)
{
	g_return_val_if_fail (window->priv != NULL, FALSE);

	window->priv->seek_in_progress = TRUE;
	return FALSE;
}

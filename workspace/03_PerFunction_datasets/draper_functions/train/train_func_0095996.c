gth_window_apply_saved_size (GthWindow *window,
			     int        page)
{
	g_return_if_fail (window != NULL);
	g_return_if_fail (GTH_IS_WINDOW (window));
	g_return_if_fail (page >= 0 && page < window->priv->n_pages);

	if (! window->priv->window_size[page].saved)
		return;

	gtk_window_resize (GTK_WINDOW (window),
			   window->priv->window_size[page].width,
			   window->priv->window_size[page].height);
}

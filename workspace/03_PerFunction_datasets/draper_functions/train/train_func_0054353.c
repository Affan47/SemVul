gedit_window_close_all_tabs (GeditWindow *window)
{
	g_return_if_fail (GEDIT_IS_WINDOW (window));
	g_return_if_fail (!(window->priv->state & GEDIT_WINDOW_STATE_SAVING));

	window->priv->removing_tabs = TRUE;

	gedit_multi_notebook_close_all_tabs (window->priv->multi_notebook);

	window->priv->removing_tabs = FALSE;
}

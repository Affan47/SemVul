gitg_window_activate (GitgWindow  *window,
                      gchar const *activatable,
                      gchar const *action)
{
	GSList *item;

	g_return_val_if_fail (GITG_IS_WINDOW (window), FALSE);
	g_return_val_if_fail (activatable != NULL, FALSE);

	for (item = window->priv->activatables; item; item = g_slist_next (item))
	{
		GitgActivatable *act = item->data;
		gchar *id;
		gboolean match;

		id = gitg_activatable_get_id (act);
		match = g_strcmp0 (activatable, id) == 0;
		g_free (id);

		if (match)
		{
			return activate_activatable (window, act, action);
		}
	}

	return FALSE;
}

log_matches_cb (GiggleGit *git,
		 GiggleJob *job,
		 GError    *error,
		 gpointer   user_data)
{
	RevisionSearchData     *data;
	GiggleRevListViewPriv *priv;
	const gchar            *log;
	gchar                  *casefold_log;

	data = (RevisionSearchData *) user_data;
	priv = GET_PRIV (data->list);

	if (error) {
		data->match = FALSE;
	} else {
		log = giggle_git_log_get_log (GIGGLE_GIT_LOG (job));
		casefold_log = g_utf8_casefold (log, -1);
		data->match = (strstr (casefold_log, data->search_term) != NULL);

		g_free (casefold_log);
	}

	g_clear_object (&priv->job);

	g_main_loop_quit (data->main_loop);
}

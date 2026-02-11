git_revisions_get_committer_info (GiggleGitRevisionsPriv  *priv,
				  GiggleRevision          *revision,
				  const gchar             *line,
				  GiggleAuthor           **author,
				  struct tm              **tm)
{
	GMatchInfo *match = NULL;
	char       *address = NULL;
	char       *timestamp = NULL;

	if (!priv->regex_committer) {
		priv->regex_committer = g_regex_new
			("^([^<]*\\s+<[^>]+>)\\s+(\\d+ [+-]\\d+)\\b",
			 G_REGEX_OPTIMIZE, 0, NULL);
	}

	if (g_regex_match (priv->regex_committer, line, 0, &match)) {
		address   = g_match_info_fetch (match, 1);
		timestamp = g_match_info_fetch (match, 2);
	}

	g_match_info_free (match);

	if (author && address)
		*author = giggle_author_new_from_string (address);
	if (tm && timestamp)
		*tm = git_revisions_get_time (timestamp);

	g_free (timestamp);
	g_free (address);
}

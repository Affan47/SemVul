git_list_tree_command_handle_output (GitCommand *git_command,
									 const gchar *output)
{
	GitListTreeCommand *self;
	GMatchInfo *match_info;
	gchar *blob_sha;
	gchar *filename;

	self = GIT_LIST_TREE_COMMAND (git_command);
	match_info = NULL;

	if (g_regex_match (self->priv->blob_regex, output, 0, &match_info))
	{
		blob_sha = g_match_info_fetch (match_info, 1);
		filename = g_match_info_fetch (match_info, 2);

		g_hash_table_insert (self->priv->blobs, g_strdup (filename),
							 g_strdup (blob_sha));

		g_free (blob_sha);
		g_free (filename);
	}

	if (match_info)
		g_match_info_free (match_info);
}

write_tree (GitgCommit *commit, gchar **tree, GError **error)
{
	gchar **lines;
	gboolean retval;

	retval = gitg_shell_run_sync_with_output (gitg_command_new (commit->priv->repository,
	                                                            "write-tree",
	                                                            NULL),
	                                          FALSE,
	                                          &lines,
	                                          error);

	if (!retval || !lines || strlen (*lines) != GITG_HASH_SHA_SIZE)
	{
		g_strfreev (lines);
		return FALSE;
	}

	*tree = g_strdup (*lines);
	g_strfreev (lines);

	return TRUE;
}

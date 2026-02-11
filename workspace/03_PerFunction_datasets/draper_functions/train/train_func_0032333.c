update_index_staged (GitgCommit      *commit,
                     GitgChangedFile *file)
{
	GFile *f = gitg_changed_file_get_file (file);
	gchar *path = gitg_repository_relative (commit->priv->repository, f);
	gchar *head = gitg_repository_parse_head (commit->priv->repository);
	gboolean retval;
	gchar **ret;

	retval = gitg_shell_run_sync_with_output (gitg_command_new (commit->priv->repository,
	                                                                  "diff-index",
	                                                                  "--no-ext-diff",
	                                                                  "--cached",
	                                                                  head,
	                                                                  "--",
	                                                                  path,
	                                                                  NULL),
	                                               FALSE,
	                                               &ret,
	                                               NULL);

	g_free (path);
	g_free (head);
	g_object_unref (f);

	if (!retval)
	{
		g_strfreev (ret);
		return;
	}

	gchar **parts = *ret ? g_strsplit_set (*ret, " \t", 0) : NULL;
	g_strfreev (ret);

	if (parts && g_strv_length (parts) > 2)
	{
		gitg_changed_file_set_mode (file, parts[0] + 1);
		gitg_changed_file_set_sha (file, parts[2]);

		gitg_changed_file_set_changes (file,
		                               gitg_changed_file_get_changes (file) |
		                               GITG_CHANGED_FILE_CHANGES_CACHED);

		update_changed_file_status (file, parts[4], parts[0] + 1);
	}
	else
	{
		gitg_changed_file_set_changes (file,
		                               gitg_changed_file_get_changes (file) &
		                               ~GITG_CHANGED_FILE_CHANGES_CACHED);
	}

	if (parts)
	{
		g_strfreev (parts);
	}
}

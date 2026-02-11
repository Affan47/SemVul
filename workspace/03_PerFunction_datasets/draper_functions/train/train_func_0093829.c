gitg_command_set_argumentsv (GitgCommand         *command,
                             gchar const * const *arguments)
{
	GPtrArray *ret;

	g_return_if_fail (GITG_IS_COMMAND (command));

	ret = g_ptr_array_new ();

	if (command->priv->repository)
	{
		GFile *git_dir;
		GFile *work_tree;

		gchar *git_dir_path;
		gchar *work_tree_path;

		git_dir = gitg_repository_get_git_dir (command->priv->repository);
		work_tree = gitg_repository_get_work_tree (command->priv->repository);

		git_dir_path = g_file_get_path (git_dir);
		work_tree_path = g_file_get_path (work_tree);

		g_object_unref (git_dir);
		g_object_unref (work_tree);

		g_ptr_array_add (ret, g_strdup ("git"));
		g_ptr_array_add (ret, g_strdup ("--git-dir"));
		g_ptr_array_add (ret, git_dir_path);
		g_ptr_array_add (ret, g_strdup ("--work-tree"));
		g_ptr_array_add (ret, work_tree_path);
	}

	while (*arguments)
	{
		g_ptr_array_add (ret, g_strdup (*arguments++));
	}

	g_ptr_array_add (ret, NULL);

	g_strfreev (command->priv->arguments);
	command->priv->arguments = (gchar **)g_ptr_array_free (ret, FALSE);

	g_object_notify (G_OBJECT (command), "arguments");
}

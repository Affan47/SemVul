file_list_get_path_and_ignore_for_iter (GiggleFileList   *list,
					GtkTreeIter      *iter,
					gchar           **path,
					GiggleGitIgnore **git_ignore)
{
	GiggleFileListPriv *priv;
	GtkTreeIter         parent;

	priv = GET_PRIV (list);

	if (!gtk_tree_model_iter_parent (priv->filter_model, &parent, iter)) {
		if (path) {
			*path = NULL;
		}

		if (git_ignore) {
			*git_ignore = NULL;
		}

		return FALSE;
	}

	if (path) {
		gtk_tree_model_get (GTK_TREE_MODEL (priv->filter_model), iter,
				    COL_REL_PATH, path,
				    -1);
	}

	if (git_ignore) {
		gtk_tree_model_get (GTK_TREE_MODEL (priv->filter_model), &parent,
				    COL_GIT_IGNORE, git_ignore,
				    -1);
	}

	return TRUE;
}

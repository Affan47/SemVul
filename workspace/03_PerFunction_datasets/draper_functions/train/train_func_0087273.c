git_ignore_finalize (GObject *object)
{
	GiggleGitIgnorePriv *priv;

	priv = GIGGLE_GIT_IGNORE (object)->priv;

	g_object_unref (priv->git);
	g_free (priv->directory_path);
	g_free (priv->relative_path);

	if (priv->globs) {
		g_ptr_array_foreach (priv->globs, (GFunc) g_free, NULL);
		g_ptr_array_free (priv->globs, TRUE);
	}

	if (priv->global_globs) {
		g_ptr_array_foreach (priv->global_globs, (GFunc) g_free, NULL);
		g_ptr_array_free (priv->global_globs, TRUE);
	}

	G_OBJECT_CLASS (giggle_git_ignore_parent_class)->finalize (object);
}

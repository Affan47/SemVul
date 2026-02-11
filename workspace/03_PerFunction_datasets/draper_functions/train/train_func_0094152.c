git_remote_list_finalize (GObject *object)
{
	GiggleGitRemoteListPriv *priv;

	priv = GET_PRIV (object);

	while (priv->names) {
		g_free (priv->names->data);
		priv->names = g_list_delete_link (priv->names, priv->names);
	}

	G_OBJECT_CLASS (giggle_git_remote_list_parent_class)->finalize (object);
}

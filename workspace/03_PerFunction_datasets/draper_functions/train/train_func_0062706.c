initialize_commit (GitgCommitView *self)
{
	if (self->priv->commit)
	{
		return;
	}

	self->priv->commit = gitg_commit_new (self->priv->repository);

	g_signal_connect (self->priv->commit,
	                  "inserted",
	                  G_CALLBACK (on_commit_file_inserted),
	                  self);

	g_signal_connect (self->priv->commit,
	                  "removed",
	                  G_CALLBACK (on_commit_file_removed),
	                  self);

	gitg_commit_refresh (self->priv->commit);
}

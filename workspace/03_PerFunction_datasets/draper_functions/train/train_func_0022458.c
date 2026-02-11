giggle_git_cancel_job (GiggleGit *git, GiggleJob *job)
{
	GiggleGitPriv *priv;
	guint          id;

	g_return_if_fail (GIGGLE_IS_GIT (git));
	g_return_if_fail (GIGGLE_IS_JOB (job));

	priv = git->priv;

	g_object_get (job, "id", &id, NULL);

	giggle_dispatcher_cancel (priv->dispatcher, id);

	g_hash_table_remove (priv->jobs, GINT_TO_POINTER (id));
}

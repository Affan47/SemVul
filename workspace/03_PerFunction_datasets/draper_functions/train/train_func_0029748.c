gitg_repository_reload (GitgRepository *repository)
{
	g_return_if_fail (GITG_IS_REPOSITORY (repository));
	g_return_if_fail (repository->priv->git_dir != NULL);

	gitg_io_cancel (GITG_IO (repository->priv->loader));

	repository->priv->load_stage = LOAD_STAGE_NONE;
	gitg_repository_clear (repository);

	load_refs (repository);
	reload_revisions (repository, NULL);
}

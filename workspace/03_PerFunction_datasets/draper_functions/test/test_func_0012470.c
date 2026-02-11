gitg_repository_get_current_working_ref (GitgRepository *repository)
{
	if (repository->priv->working_ref)
	{
		return repository->priv->working_ref;
	}

	repository->priv->working_ref = get_current_working_ref (repository);
	return repository->priv->working_ref;
}

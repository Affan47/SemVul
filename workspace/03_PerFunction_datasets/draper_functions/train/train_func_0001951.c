submodule_is_config_only(
	checkout_data *data,
	const char *path)
{
	git_submodule *sm = NULL;
	unsigned int sm_loc = 0;

	if (git_submodule_lookup(&sm, data->repo, path) < 0 ||
		git_submodule_location(&sm_loc, sm) < 0 ||
		sm_loc == GIT_SUBMODULE_STATUS_IN_CONFIG)
		return true;

	return false;
}

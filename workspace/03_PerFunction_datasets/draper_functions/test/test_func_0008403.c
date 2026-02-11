maybe_modified_submodule(
	git_delta_t *status,
	git_oid *found_oid,
	git_diff_list *diff,
	diff_in_progress *info)
{
	int error = 0;
	git_submodule *sub;
	unsigned int sm_status = 0;
	const git_oid *sm_oid;

	*status = GIT_DELTA_UNMODIFIED;

	if (!DIFF_FLAG_IS_SET(diff, GIT_DIFF_IGNORE_SUBMODULES) &&
		!(error = git_submodule_lookup(
			  &sub, diff->repo, info->nitem->path)) &&
		git_submodule_ignore(sub) != GIT_SUBMODULE_IGNORE_ALL &&
		!(error = git_submodule_status(&sm_status, sub)))
	{


		if (!GIT_SUBMODULE_STATUS_IS_WD_UNMODIFIED(sm_status))
			*status = GIT_DELTA_MODIFIED;


		if (git_oid_iszero(&info->nitem->oid) &&
			(sm_oid = git_submodule_wd_id(sub)) != NULL)
			git_oid_cpy(found_oid, sm_oid);
	}


	if (error == GIT_EEXISTS) {
		giterr_clear();
		error = 0;
	}

	return error;
}

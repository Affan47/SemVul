reference_matches_remote_head(
	const char *reference_name,
	void *payload)
{
	struct head_info *head_info = (struct head_info *)payload;
	git_oid oid;


	if (git_buf_len(&head_info->branchname) > 0)
		return 0;

	if (git_reference_name_to_oid(
		&oid,
		head_info->repo,
		reference_name) < 0) {


			return -1;
	}

	if (git_oid_cmp(&head_info->remote_head_oid, &oid) == 0) {

		if (git_refspec_transform_l(
			&head_info->branchname,
			head_info->refspec,
			reference_name) < 0)
				return -1;

		if (git_buf_sets(
			&head_info->branchname,
			git_buf_cstr(&head_info->branchname) + strlen(GIT_REFS_HEADS_DIR)) < 0)
				return -1;
	}

	return 0;
}

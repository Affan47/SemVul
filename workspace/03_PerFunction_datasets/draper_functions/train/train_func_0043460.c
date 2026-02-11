diff_delta__merge_like_cgit_reversed(
	const git_diff_delta *a,
	const git_diff_delta *b,
	git_pool *pool)
{
	git_diff_delta *dup;


	if (a->status == GIT_DELTA_UNMODIFIED)
		return diff_delta__dup(b, pool);

	if ((dup = diff_delta__dup(a, pool)) == NULL)
		return NULL;

	if (b->status == GIT_DELTA_UNMODIFIED || b->status == GIT_DELTA_UNTRACKED || b->status == GIT_DELTA_UNREADABLE)
		return dup;

	if (dup->status == GIT_DELTA_DELETED) {
		if (b->status == GIT_DELTA_ADDED)
			dup->status = GIT_DELTA_UNMODIFIED;
	} else {
		dup->status = b->status;
	}

	git_oid_cpy(&dup->old_file.id, &b->old_file.id);
	dup->old_file.mode  = b->old_file.mode;
	dup->old_file.size  = b->old_file.size;
	dup->old_file.flags = b->old_file.flags;

	return dup;
}

diff_delta__from_two(
	git_diff_list *diff,
	git_delta_t   status,
	const git_index_entry *old_entry,
	const git_index_entry *new_entry,
	git_oid *new_oid)
{
	git_diff_delta *delta;

	if (status == GIT_DELTA_UNMODIFIED &&
		(diff->opts.flags & GIT_DIFF_INCLUDE_UNMODIFIED) == 0)
		return 0;

	if ((diff->opts.flags & GIT_DIFF_REVERSE) != 0) {
		const git_index_entry *temp = old_entry;
		old_entry = new_entry;
		new_entry = temp;
	}

	delta = diff_delta__alloc(diff, status, old_entry->path);
	GITERR_CHECK_ALLOC(delta);

	delta->old_file.mode = old_entry->mode;
	git_oid_cpy(&delta->old_file.oid, &old_entry->oid);
	delta->old_file.flags |= GIT_DIFF_FILE_VALID_OID;

	delta->new_file.mode = new_entry->mode;
	git_oid_cpy(&delta->new_file.oid, new_oid ? new_oid : &new_entry->oid);
	if (new_oid || !git_oid_iszero(&new_entry->oid))
		delta->new_file.flags |= GIT_DIFF_FILE_VALID_OID;

	if (git_vector_insert(&diff->deltas, delta) < 0) {
		git__free(delta);
		return -1;
	}

	return 0;
}

diff_print_patch_file_binary(
	diff_print_info *pi, const git_diff_delta *delta,
	const char *oldpfx, const char *newpfx)
{
	git_blob *old = NULL, *new = NULL;
	const git_oid *old_id, *new_id;
	int error;
	size_t pre_binary_size;

	if ((pi->flags & GIT_DIFF_SHOW_BINARY) == 0)
		goto noshow;

	pre_binary_size = pi->buf->size;
	git_buf_printf(pi->buf, "GIT binary patch\n");
	pi->line.num_lines++;

	old_id = (delta->status != GIT_DELTA_ADDED) ? &delta->old_file.id : NULL;
	new_id = (delta->status != GIT_DELTA_DELETED) ? &delta->new_file.id : NULL;

	if (old_id && (error = git_blob_lookup(&old, pi->diff->repo, old_id)) < 0)
		goto done;
	if (new_id && (error = git_blob_lookup(&new, pi->diff->repo,new_id)) < 0)
		goto done;

	if ((error = print_binary_hunk(pi, old, new)) < 0 ||
		(error = git_buf_putc(pi->buf, '\n')) < 0 ||
		(error = print_binary_hunk(pi, new, old)) < 0)
	{
		if (error == GIT_EBUFS) {
			giterr_clear();
			git_buf_truncate(pi->buf, pre_binary_size);
			goto noshow;
		}
	}

	pi->line.num_lines++;

done:
	git_blob_free(old);
	git_blob_free(new);

	return error;

noshow:
	pi->line.num_lines = 1;
	return diff_delta_format_with_paths(
		pi->buf, delta, oldpfx, newpfx,
		"Binary files %s%s and %s%s differ\n");
}

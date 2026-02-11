checkout_remove_the_old(
	git_diff_list *diff,
	unsigned int *actions,
	checkout_diff_data *data)
{
	git_diff_delta *delta;
	size_t i;

	git_buf_truncate(data->path, data->workdir_len);

	git_vector_foreach(&diff->deltas, i, delta) {
		if (actions[i] & CHECKOUT_ACTION__REMOVE) {
			int error = git_futils_rmdir_r(
				delta->new_file.path,
				git_buf_cstr(data->path),
				GIT_RMDIR_REMOVE_FILES | GIT_RMDIR_EMPTY_PARENTS |
				GIT_RMDIR_REMOVE_BLOCKERS);
			if (error < 0)
				return error;

			data->completed_steps++;
			report_progress(data, delta->new_file.path);
		}
	}

	return 0;
}

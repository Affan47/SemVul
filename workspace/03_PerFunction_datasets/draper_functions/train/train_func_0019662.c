diff_delta__alloc(
	git_diff_list *diff,
	git_delta_t status,
	const char *path)
{
	git_diff_delta *delta = git__calloc(1, sizeof(git_diff_delta));
	if (!delta)
		return NULL;

	delta->old_file.path = git_pool_strdup(&diff->pool, path);
	if (delta->old_file.path == NULL) {
		git__free(delta);
		return NULL;
	}

	delta->new_file.path = delta->old_file.path;

	if (diff->opts.flags & GIT_DIFF_REVERSE) {
		switch (status) {
		case GIT_DELTA_ADDED:   status = GIT_DELTA_DELETED; break;
		case GIT_DELTA_DELETED: status = GIT_DELTA_ADDED; break;
		default: break;
		}
	}
	delta->status = status;

	return delta;
}

fs_iterator__initialize(
	git_iterator **out, fs_iterator *fi, const char *root)
{
	int error;

	if (git_buf_sets(&fi->path, root) < 0 || git_path_to_dir(&fi->path) < 0) {
		git__free(fi);
		return -1;
	}
	fi->root_len = fi->path.size;

	if ((error = fs_iterator__expand_dir(fi)) == GIT_ENOTFOUND) {
		giterr_clear();
		error = 0;
	}
	if (error) {
		git_iterator_free((git_iterator *)fi);
		fi = NULL;
	}

	*out = (git_iterator *)fi;
	return error;
}

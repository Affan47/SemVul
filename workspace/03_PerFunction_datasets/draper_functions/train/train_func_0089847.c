fs_iterator__expand_dir(fs_iterator *fi)
{
	int error;
	fs_iterator_frame *ff;

	if (fi->depth > FS_MAX_DEPTH) {
		giterr_set(GITERR_REPOSITORY,
			"Directory nesting is too deep (%d)", fi->depth);
		return -1;
	}

	ff = fs_iterator__alloc_frame(fi);
	GITERR_CHECK_ALLOC(ff);

	error = git_path_dirload_with_stat(
		fi->path.ptr, fi->root_len, iterator__ignore_case(fi),
		fi->base.start, fi->base.end, &ff->entries);

	if (error < 0 || ff->entries.length == 0) {
		fs_iterator__free_frame(ff);
		return GIT_ENOTFOUND;
	}

	fs_iterator__seek_frame_start(fi, ff);

	ff->next  = fi->stack;
	fi->stack = ff;
	fi->depth++;

	if (fi->enter_dir_cb && (error = fi->enter_dir_cb(fi)) < 0)
		return error;

	return fs_iterator__update_entry(fi);
}

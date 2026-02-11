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
		fi->path.ptr, fi->root_len, fi->dirload_flags,
		fi->base.start, fi->base.end, &ff->entries);

	if (error < 0) {
		git_error_state last_error = { 0 };
		giterr_capture(&last_error, error);


		fs_iterator__free_frame(ff);
		fs_iterator__advance_over(NULL, (git_iterator *)fi);

		fi->base.flags &= ~GIT_ITERATOR_FIRST_ACCESS;

		return giterr_restore(&last_error);
	}

	if (ff->entries.length == 0) {
		fs_iterator__free_frame(ff);
		return GIT_ENOTFOUND;
	}
	fi->base.stat_calls += ff->entries.length;

	fs_iterator__seek_frame_start(fi, ff);

	ff->next  = fi->stack;
	fi->stack = ff;
	fi->depth++;

	if (fi->enter_dir_cb && (error = fi->enter_dir_cb(fi)) < 0)
		return error;

	return fs_iterator__update_entry(fi);
}

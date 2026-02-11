read_from_tree(const char *prefix, const char **argv,
		unsigned char *tree_sha1, int refresh_flags)
{
	struct lock_file *lock = xcalloc(1, sizeof(struct lock_file));
	int index_fd, index_was_discarded = 0;
	struct diff_options opt;

	memset(&opt, 0, sizeof(opt));
	diff_tree_setup_paths(get_pathspec(prefix, (const char **)argv), &opt);
	opt.output_format = DIFF_FORMAT_CALLBACK;
	opt.format_callback = update_index_from_diff;
	opt.format_callback_data = &index_was_discarded;

	index_fd = hold_locked_index(lock, 1);
	index_was_discarded = 0;
	read_cache();
	if (do_diff_cache(tree_sha1, &opt))
		return 1;
	diffcore_std(&opt);
	diff_flush(&opt);
	diff_tree_release_paths(&opt);

	if (!index_was_discarded)

		discard_cache();
	return update_index_refresh(index_fd, lock, refresh_flags);
}

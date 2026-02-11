write_archive_entries(struct archiver_args *args,
		write_archive_entry_fn_t write_entry)
{
	struct archiver_context context;
	struct unpack_trees_options opts;
	struct tree_desc t;
	struct pathspec pathspec;
	int err;

	if (args->baselen > 0 && args->base[args->baselen - 1] == '/') {
		size_t len = args->baselen;

		while (len > 1 && args->base[len - 2] == '/')
			len--;
		if (args->verbose)
			fprintf(stderr, "%.*s\n", (int)len, args->base);
		err = write_entry(args, args->tree->object.sha1, args->base,
				len, 040777, NULL, 0);
		if (err)
			return err;
	}

	context.args = args;
	context.write_entry = write_entry;


	if (!args->worktree_attributes) {
		memset(&opts, 0, sizeof(opts));
		opts.index_only = 1;
		opts.head_idx = -1;
		opts.src_index = &the_index;
		opts.dst_index = &the_index;
		opts.fn = oneway_merge;
		init_tree_desc(&t, args->tree->buffer, args->tree->size);
		if (unpack_trees(1, &t, &opts))
			return -1;
		git_attr_set_direction(GIT_ATTR_INDEX, &the_index);
	}

	init_pathspec(&pathspec, args->pathspec);
	err = read_tree_recursive(args->tree, "", 0, 0, &pathspec,
				  write_archive_entry, &context);
	free_pathspec(&pathspec);
	if (err == READ_TREE_RECURSIVE)
		err = 0;
	return err;
}

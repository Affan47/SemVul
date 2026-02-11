switch_ctr(struct dm_target *ti, unsigned argc, char **argv)
{
	static struct dm_arg _args[] = {
		{1, (KMALLOC_MAX_SIZE - sizeof(struct switch_ctx)) / sizeof(struct switch_path), "Invalid number of paths"},
		{1, UINT_MAX, "Invalid region size"},
		{0, 0, "Invalid number of optional args"},
	};

	struct switch_ctx *sctx;
	struct dm_arg_set as;
	unsigned nr_paths, region_size, nr_optional_args;
	int r;

	as.argc = argc;
	as.argv = argv;

	r = dm_read_arg(_args, &as, &nr_paths, &ti->error);
	if (r)
		return -EINVAL;

	r = dm_read_arg(_args + 1, &as, &region_size, &ti->error);
	if (r)
		return r;

	r = dm_read_arg_group(_args + 2, &as, &nr_optional_args, &ti->error);
	if (r)
		return r;


	if (as.argc != nr_paths * 2) {
		ti->error = "Incorrect number of path arguments";
		return -EINVAL;
	}

	sctx = alloc_switch_ctx(ti, nr_paths, region_size);
	if (!sctx) {
		ti->error = "Cannot allocate redirection context";
		return -ENOMEM;
	}

	r = dm_set_target_max_io_len(ti, region_size);
	if (r)
		goto error;

	while (as.argc) {
		r = parse_path(&as, ti);
		if (r)
			goto error;
	}

	r = alloc_region_table(ti, nr_paths);
	if (r)
		goto error;

	initialise_region_table(sctx);


	ti->num_discard_bios = 1;

	return 0;

error:
	switch_dtr(ti);

	return r;
}

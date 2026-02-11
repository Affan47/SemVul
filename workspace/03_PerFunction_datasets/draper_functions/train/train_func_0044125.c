main(int argc, char *argv[])
{
	int rc;
	command_t cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.options.pic_mode = PIC_UNKNOWN;
	cmd.mode = MODE_UNKNOWN;
	cmd.output = OUT_GENERAL;


	cmd.program_opts		= alloc_countchars();
	cmd.arglist			= alloc_countchars();
	cmd.tmp_dirs 			= alloc_countchars();
	cmd.obj_files			= alloc_countchars();
	cmd.dep_rpaths 			= alloc_countchars();
	cmd.rpaths			= alloc_countchars();
	cmd.static_opts.normal		= alloc_countchars();
	cmd.shared_opts.normal		= alloc_countchars();
	cmd.shared_opts.dependencies	= alloc_countchars();


	parse_args(argc, argv, &cmd);
	post_parse_fixup(&cmd);


	if (cmd.mode == MODE_UNKNOWN) {
		usage(1);
	}

	rc = run_mode(&cmd);
	if (!rc) {
		add_for_runtime(&cmd);
	}

	cleanup_tmp_dirs(&cmd);

	return rc;
}

glfs_set_volfile (struct glfs *fs, const char *volfile)
{
	cmd_args_t  *cmd_args = NULL;

	cmd_args = &fs->ctx->cmd_args;

	if (vol_assigned (cmd_args))
		return -1;

	cmd_args->volfile = gf_strdup (volfile);

	return 0;
}

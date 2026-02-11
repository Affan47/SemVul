get_volfp (struct glfs *fs)
{
	int	     ret = 0;
	cmd_args_t  *cmd_args = NULL;
	FILE	    *specfp = NULL;
	struct stat  statbuf;

	cmd_args = &fs->ctx->cmd_args;

	ret = lstat (cmd_args->volfile, &statbuf);
	if (ret == -1) {
		gf_log ("glfs", GF_LOG_ERROR,
			"%s: %s", cmd_args->volfile, strerror (errno));
		return NULL;
	}

	if ((specfp = fopen (cmd_args->volfile, "r")) == NULL) {
		gf_log ("glfs", GF_LOG_ERROR,
			"volume file %s: %s",
			cmd_args->volfile,
			strerror (errno));
		return NULL;
	}

	gf_log ("glfs", GF_LOG_DEBUG,
		"loading volume file %s", cmd_args->volfile);

	return specfp;
}

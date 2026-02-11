glfs_set_volfile_server (struct glfs *fs, const char *transport,
			 const char *host, int port)
{
	cmd_args_t  *cmd_args = NULL;

	cmd_args = &fs->ctx->cmd_args;

	if (vol_assigned (cmd_args))
		return -1;

	cmd_args->volfile_server = gf_strdup (host);
	cmd_args->volfile_server_transport = gf_strdup (transport);
	cmd_args->volfile_server_port = port;
	cmd_args->max_connect_attempts = 2;

	return 0;
}

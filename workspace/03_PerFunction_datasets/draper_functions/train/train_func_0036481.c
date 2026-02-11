gfs_client_command_send_signal(struct gfs_connection *gfs_server, int sig)
{
	gfarm_error_t e;
	struct gfs_client_command_context *cc = gfs_server->context;

	while (gfs_client_command_is_running(gfs_server) &&
	       cc->pending_signal != 0) {
		e = gfs_client_command_io(gfs_server, NULL);
		if (e != GFARM_ERR_NO_ERROR) {
			gflog_debug(GFARM_MSG_1001242,
				"gfs_client_command_io() failed: %s",
				gfarm_error_string(e));
			return (e);
		}
	}
	if (!gfs_client_command_is_running(gfs_server))
		return (gfarm_errno_to_error(ESRCH));
	cc->pending_signal = sig;

	return (gfs_client_command_io(gfs_server, NULL));
}

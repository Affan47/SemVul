download_rx_error(void *o, const char *reason, ...)
{
	struct download *d = o;
	char msg[1024];
	va_list args;

	download_check(d);


	if (
		0 == (d->server->attrs & DLS_A_PIPELINING) &&
		d->pipeline != NULL &&
		GTA_DL_PIPE_SENT == d->pipeline->status
	) {
		d->server->attrs |= DLS_A_NO_PIPELINE;

		if (GNET_PROPERTY(download_debug)) {
			g_message("disabled pipelining to %s on I/O error",
				download_host_info(d));
		}
	}

	va_start(args, reason);
	str_vbprintf(msg, sizeof msg, reason, args);
	download_repair(d, msg);
	va_end(args);
}

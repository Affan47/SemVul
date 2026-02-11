cgi_connection_close(server *srv, handler_ctx *hctx) {
	int status;
	pid_t pid;
	plugin_data *p;
	connection  *con;

	if (NULL == hctx) return HANDLER_GO_ON;

	p    = hctx->plugin_data;
	con  = hctx->remote_conn;

	if (con->mode != p->id) return HANDLER_GO_ON;

#ifndef __WIN32


	if (hctx->fd != -1) {

		fdevent_event_del(srv->ev, &(hctx->fde_ndx), hctx->fd);
		fdevent_unregister(srv->ev, hctx->fd);

		if (close(hctx->fd)) {
			log_error_write(srv, __FILE__, __LINE__, "sds", "cgi close failed ", hctx->fd, strerror(errno));
		}

		hctx->fd = -1;
		hctx->fde_ndx = -1;
	}

	pid = hctx->pid;

	con->plugin_ctx[p->id] = NULL;


	cgi_handler_ctx_free(hctx);


	if (pid) {

		switch(waitpid(pid, &status, WNOHANG)) {
		case 0:

#if 0
			log_error_write(srv, __FILE__, __LINE__, "sd", "(debug) child isn't done yet, pid:", pid);
#endif
			break;
		case -1:

			if (errno == EINTR) break;


			if (errno == ECHILD) return HANDLER_GO_ON;

			log_error_write(srv, __FILE__, __LINE__, "ss", "waitpid failed: ", strerror(errno));
			return HANDLER_ERROR;
		default:

			if (0 == con->file_started) {
				connection_set_state(srv, con, CON_STATE_HANDLE_REQUEST);
				con->http_status = 500;
				con->mode = DIRECT;
			}

			if (WIFEXITED(status)) {
#if 0
				log_error_write(srv, __FILE__, __LINE__, "sd", "(debug) cgi exited fine, pid:", pid);
#endif
				return HANDLER_GO_ON;
			} else {
				log_error_write(srv, __FILE__, __LINE__, "sd", "cgi died, pid:", pid);
				return HANDLER_GO_ON;
			}
		}


		kill(pid, SIGTERM);


		cgi_pid_add(srv, p, pid);
	}
#endif
	return HANDLER_GO_ON;
}

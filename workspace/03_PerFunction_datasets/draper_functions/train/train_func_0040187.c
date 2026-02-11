gfm_server_generation_updated(struct peer *peer, int from_client, int skip)
{
	gfarm_error_t e;
	gfarm_int32_t fd, result;
	struct host *spool_host;
	struct process *process;
	static const char diag[] = "GFM_PROTO_GENERATION_UPDATED";

	e = gfm_server_get_request(peer, diag, "i", &result);
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1002265, "%s request failed: %s",
		    diag, gfarm_error_string(e));
		return (e);
	}
	if (skip)
		return (GFARM_ERR_NO_ERROR);
	giant_lock();

	if (from_client) {
		gflog_debug(GFARM_MSG_1002266, "%s: from client", diag);
		e = GFARM_ERR_OPERATION_NOT_PERMITTED;
	} else if ((spool_host = peer_get_host(peer)) == NULL) {
		gflog_debug(GFARM_MSG_1002267,
		    "%s: peer_get_host() failed", diag);
		e = GFARM_ERR_OPERATION_NOT_PERMITTED;
	} else if ((process = peer_get_process(peer)) == NULL) {
		gflog_debug(GFARM_MSG_1002268,
		    "%s: peer_get_process() failed", diag);
		e = GFARM_ERR_OPERATION_NOT_PERMITTED;
	} else if ((e = peer_fdpair_get_current(peer, &fd)) !=
	    GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1002269,
		    "%s: peer_fdpair_get_current() failed: %s",
		    diag, gfarm_error_string(e));
	} else if ((e = process_new_generation_done(process, peer, fd, result))
	    != GFARM_ERR_NO_ERROR) {
		gflog_warning(GFARM_MSG_1002270,
		    "%s: host %s, fd %d: new generation wakeup(%s): %s\n",
		    diag, host_name(spool_host), fd,
		    gfarm_error_string(result), gfarm_error_string(e));
	} else if (result != GFARM_ERR_NO_ERROR) {
		gflog_warning(GFARM_MSG_1002271,
		    "%s: host %s, fd %d: new generation rename: %s\n", diag,
		    host_name(spool_host), fd, gfarm_error_string(result));
	}

	giant_unlock();
	return (gfm_server_put_reply(peer, diag, e, ""));
}

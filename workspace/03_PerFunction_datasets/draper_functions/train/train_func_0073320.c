close_write_v2_4_resume(struct peer *peer, void *closure, int *suspendedp)
{
	gfarm_error_t e;
	struct close_v2_4_resume_arg *arg = closure;
	struct host *spool_host;
	struct process *process;
	int transaction = 0;
	gfarm_int32_t flags;
	gfarm_int64_t old_gen = 0, new_gen = 0;
	static const char diag[] = "close_v2_4_resume";

	giant_lock();

	if ((spool_host = peer_get_host(peer)) == NULL) {
		gflog_debug(GFARM_MSG_1002263,
		    "%s: peer_get_host() failed", diag);
		e = GFARM_ERR_OPERATION_NOT_PERMITTED;
	} else if ((process = peer_get_process(peer)) == NULL) {
		gflog_debug(GFARM_MSG_1002264,
		    "%s: peer_get_process() failed", diag);
		e = GFARM_ERR_OPERATION_NOT_PERMITTED;
	} else {
		if (db_begin(diag) == GFARM_ERR_NO_ERROR)
			transaction = 1;


		e = process_close_file_write(process, peer, arg->fd, arg->size,
		    &arg->atime, &arg->mtime, &flags, &old_gen, &new_gen);
		if (transaction)
			db_end(diag);

		if (e == GFARM_ERR_NO_ERROR)
			e = peer_fdpair_close_current(peer);
		else if (e == GFARM_ERR_RESOURCE_TEMPORARILY_UNAVAILABLE) {
			if ((e = process_new_generation_wait(peer, arg->fd,
			    close_write_v2_4_resume, arg)) ==
			    GFARM_ERR_NO_ERROR) {
				*suspendedp = 1;
				giant_unlock();
				return (GFARM_ERR_NO_ERROR);
			}
		}
	}
	free(arg);
	giant_unlock();
	return (gfm_server_put_reply(peer, diag, e, "ill",
	    flags, old_gen, new_gen));
}

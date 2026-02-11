replica_adding_resume(struct peer *peer, void *closure, int *suspendedp)
{
	gfarm_error_t e;
	struct replica_adding_resume_arg *arg = closure;
	struct host *spool_host;
	struct process *process;
	struct host *src;
	struct inode *inode;
	gfarm_ino_t inum = 0;
	gfarm_uint64_t gen = 0;
	struct gfarm_timespec *mtime;
	gfarm_int64_t mtime_sec = 0;
	gfarm_int32_t mtime_nsec = 0;
	static const char diag[] = "replica_adding_resume";

	giant_lock();

	if ((spool_host = peer_get_host(peer)) == NULL) {
		gflog_debug(GFARM_MSG_1002272,
		    "%s: peer_get_host() failed", diag);
		e = GFARM_ERR_OPERATION_NOT_PERMITTED;
	} else if ((process = peer_get_process(peer)) == NULL) {
		gflog_debug(GFARM_MSG_1002273,
		    "%s: peer_get_process() failed", diag);
		e = GFARM_ERR_OPERATION_NOT_PERMITTED;
	} else if ((src = host_lookup(arg->src_host)) == NULL) {
		e = GFARM_ERR_UNKNOWN_HOST;
	} else if ((e = process_replica_adding(process, peer,
	    src, spool_host, arg->fd, &inode)) ==
	    GFARM_ERR_RESOURCE_TEMPORARILY_UNAVAILABLE) {
		if ((e = process_new_generation_wait(peer, arg->fd,
		    replica_adding_resume, arg)) ==
		    GFARM_ERR_NO_ERROR) {
			*suspendedp = 1;
			giant_unlock();
			return (GFARM_ERR_NO_ERROR);
		}
	} else if (e != GFARM_ERR_NO_ERROR)
		;
	else {
		inum = inode_get_number(inode);
		gen = inode_get_gen(inode);
		mtime = inode_get_mtime(inode);
		mtime_sec = mtime->tv_sec;
		mtime_nsec = mtime->tv_nsec;
	}


	free(arg->src_host);
	free(arg);
	giant_unlock();
	return (gfm_server_put_reply(peer, diag, e, "llli",
	    inum, gen, mtime_sec, mtime_nsec));
}

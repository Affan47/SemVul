process_replica_adding(struct process *process, struct peer *peer,
	struct host *src, struct host *dst, int fd,
	struct inode **inodep)
{
	struct file_opening *fo;
	gfarm_error_t e = process_get_file_opening(process, fd, &fo);

	if (e != GFARM_ERR_NO_ERROR)
		return (e);
	if (fo->u.f.replicating != NULL)
		return (GFARM_ERR_FILE_BUSY);
	if (inode_new_generation_is_pending(fo->inode)) {
		gflog_debug(GFARM_MSG_1002242,
		    "process_replica_adding: new_generation pending %lld:%lld",
		    (long long)inode_get_number(fo->inode),
		    (long long)inode_get_gen(fo->inode));
		return (GFARM_ERR_RESOURCE_TEMPORARILY_UNAVAILABLE);
	}

	e = process_prepare_to_replicate(process, peer, src, dst, fd,
	    GFS_REPLICATE_FILE_FORCE, &fo->u.f.replicating, inodep);
	if (e == GFARM_ERR_NO_ERROR) {
		fo->u.f.spool_opener = peer;


	}
	return (e);
}

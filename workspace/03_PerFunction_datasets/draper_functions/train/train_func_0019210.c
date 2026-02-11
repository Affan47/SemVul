process_new_generation_done(struct process *process, struct peer *peer, int fd,
	gfarm_int32_t result)
{
	struct file_opening *fo;
	gfarm_mode_t mode;
	gfarm_error_t e = process_get_file_opening(process, fd, &fo);
	static const char diag[] = "process_new_generation_done";

	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1002325,
		    "%s: pid %lld descriptor %d: %s", diag,
		    (long long)process->pid, fd, gfarm_error_string(e));
		return (e);
	} else if ((e = inode_new_generation_done(fo->inode, peer,
	    result)) == GFARM_ERR_NO_ERROR) {


		if (fo->opener != peer && fo->opener != NULL) {


			fo->u.f.spool_opener = NULL;
			fo->u.f.spool_host = NULL;
		} else {
			mode = inode_get_mode(fo->inode);
			inode_close(fo);

			file_opening_free(fo, mode);
			process->filetab[fd] = NULL;
		}
	}
	return (e);
}

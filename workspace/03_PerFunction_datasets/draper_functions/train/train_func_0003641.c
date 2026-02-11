convert_fuse_file_lock(struct fuse_file_lock *fl,
				   struct flock *flock)
{
	memset(flock, 0, sizeof(struct flock));
	flock->l_type = fl->type;
	flock->l_whence = SEEK_SET;
	flock->l_start = fl->start;
	if (fl->end == OFFSET_MAX)
		flock->l_len = 0;
	else
		flock->l_len = fl->end - fl->start + 1;
	flock->l_pid = fl->pid;
}

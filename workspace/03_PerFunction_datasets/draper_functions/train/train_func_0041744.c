locks_remove_posix(struct file *filp, fl_owner_t owner)
{
	struct file_lock lock;
	struct file_lock_context *ctx;


	ctx =  smp_load_acquire(&file_inode(filp)->i_flctx);
	if (!ctx || list_empty(&ctx->flc_posix))
		return;

	lock.fl_type = F_UNLCK;
	lock.fl_flags = FL_POSIX | FL_CLOSE;
	lock.fl_start = 0;
	lock.fl_end = OFFSET_MAX;
	lock.fl_owner = owner;
	lock.fl_pid = current->tgid;
	lock.fl_file = filp;
	lock.fl_ops = NULL;
	lock.fl_lmops = NULL;

	vfs_lock_file(filp, F_SETLK, &lock, NULL);

	if (lock.fl_ops && lock.fl_ops->fl_release_private)
		lock.fl_ops->fl_release_private(&lock);
}

locks_remove_file(struct file *filp)
{
	struct file_lock_context *ctx;

	ctx = smp_load_acquire(&file_inode(filp)->i_flctx);
	if (!ctx)
		return;


	locks_remove_posix(filp, filp);


	locks_remove_flock(filp, ctx);


	locks_remove_lease(filp, ctx);
}

lease_get_mtime(struct inode *inode, struct timespec *time)
{
	bool has_lease = false;
	struct file_lock_context *ctx;
	struct file_lock *fl;

	ctx = smp_load_acquire(&inode->i_flctx);
	if (ctx && !list_empty_careful(&ctx->flc_lease)) {
		spin_lock(&ctx->flc_lock);
		if (!list_empty(&ctx->flc_lease)) {
			fl = list_first_entry(&ctx->flc_lease,
						struct file_lock, fl_list);
			if (fl->fl_type == F_WRLCK)
				has_lease = true;
		}
		spin_unlock(&ctx->flc_lock);
	}

	if (has_lease)
		*time = current_fs_time(inode->i_sb);
	else
		*time = inode->i_mtime;
}

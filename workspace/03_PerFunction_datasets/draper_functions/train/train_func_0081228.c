devkmsg_open(struct inode *inode, struct file *file)
{
	struct devkmsg_user *user;
	int err;


	if ((file->f_flags & O_ACCMODE) == O_WRONLY)
		return 0;

	err = check_syslog_permissions(SYSLOG_ACTION_READ_ALL,
				       SYSLOG_FROM_READER);
	if (err)
		return err;

	user = kmalloc(sizeof(struct devkmsg_user), GFP_KERNEL);
	if (!user)
		return -ENOMEM;

	mutex_init(&user->lock);

	raw_spin_lock_irq(&logbuf_lock);
	user->idx = log_first_idx;
	user->seq = log_first_seq;
	raw_spin_unlock_irq(&logbuf_lock);

	file->private_data = user;
	return 0;
}

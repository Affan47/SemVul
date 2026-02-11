kmsg_read(struct file *file, char __user *buf,
			 size_t count, loff_t *ppos)
{
	if ((file->f_flags & O_NONBLOCK) &&
	    !do_syslog(SYSLOG_ACTION_SIZE_UNREAD, NULL, 0, SYSLOG_FROM_PROC))
		return -EAGAIN;
	return do_syslog(SYSLOG_ACTION_READ, buf, count, SYSLOG_FROM_PROC);
}

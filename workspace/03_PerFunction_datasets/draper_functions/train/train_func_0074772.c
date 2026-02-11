rproc_recovery_write(struct file *filp, const char __user *user_buf,
		     size_t count, loff_t *ppos)
{
	struct rproc *rproc = filp->private_data;
	char buf[10];
	int ret;

	if (count < 1 || count > sizeof(buf))
		return count;

	ret = copy_from_user(buf, user_buf, count);
	if (ret)
		return -EFAULT;


	if (buf[count - 1] == '\n')
		buf[count - 1] = '\0';

	if (!strncmp(buf, "enabled", count)) {
		rproc->recovery_disabled = false;

		if (rproc->state == RPROC_CRASHED)
			rproc_trigger_recovery(rproc);
	} else if (!strncmp(buf, "disabled", count)) {
		rproc->recovery_disabled = true;
	} else if (!strncmp(buf, "recover", count)) {

		if (rproc->state == RPROC_CRASHED)
			rproc_trigger_recovery(rproc);
	}

	return count;
}

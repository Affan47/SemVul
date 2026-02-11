tomoyo_poll_log(struct file *file, poll_table *wait)
{
	if (tomoyo_log_count)
		return POLLIN | POLLRDNORM;
	poll_wait(file, &tomoyo_log_wait, wait);
	if (tomoyo_log_count)
		return POLLIN | POLLRDNORM;
	return 0;
}

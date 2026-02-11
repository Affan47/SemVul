mce_chrdev_poll(struct file *file, poll_table *wait)
{
	poll_wait(file, &mce_chrdev_wait, wait);
	if (READ_ONCE(mcelog.next))
		return POLLIN | POLLRDNORM;
	if (!mce_apei_read_done && apei_check_mce())
		return POLLIN | POLLRDNORM;
	return 0;
}

sonypi_misc_poll(struct file *file, poll_table *wait)
{
	poll_wait(file, &sonypi_compat.fifo_proc_list, wait);
	if (kfifo_len(&sonypi_compat.fifo))
		return POLLIN | POLLRDNORM;
	return 0;
}

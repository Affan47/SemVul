close(struct tty_struct *tty, struct file *filp)
{
	SLMP_INFO * info = tty->driver_data;

	if (sanity_check(info, tty->name, "close"))
		return;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s close() entry, count=%d\n",
			 __FILE__,__LINE__, info->device_name, info->port.count);

	if (tty_port_close_start(&info->port, tty, filp) == 0)
		goto cleanup;

	mutex_lock(&info->port.mutex);
 	if (info->port.flags & ASYNC_INITIALIZED)
 		wait_until_sent(tty, info->timeout);

	flush_buffer(tty);
	tty_ldisc_flush(tty);
	shutdown(info);
	mutex_unlock(&info->port.mutex);

	tty_port_close_end(&info->port, tty);
	info->port.tty = NULL;
cleanup:
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s close() exit, count=%d\n", __FILE__,__LINE__,
			tty->driver->name, info->port.count);
}

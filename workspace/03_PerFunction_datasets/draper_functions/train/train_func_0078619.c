ipwireless_get_serial_info(struct ipw_tty *tty,
				      struct serial_struct __user *retinfo)
{
	struct serial_struct tmp;

	if (!retinfo)
		return (-EFAULT);

	memset(&tmp, 0, sizeof(tmp));
	tmp.type = PORT_UNKNOWN;
	tmp.line = tty->index;
	tmp.port = 0;
	tmp.irq = 0;
	tmp.flags = 0;
	tmp.baud_base = 115200;
	tmp.close_delay = 0;
	tmp.closing_wait = 0;
	tmp.custom_divisor = 0;
	tmp.hub6 = 0;
	if (copy_to_user(retinfo, &tmp, sizeof(*retinfo)))
		return -EFAULT;

	return 0;
}

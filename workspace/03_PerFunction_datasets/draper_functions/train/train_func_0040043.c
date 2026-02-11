mxser_write_room(struct tty_struct *tty)
{
	struct mxser_port *info = tty->driver_data;
	int ret;

	ret = SERIAL_XMIT_SIZE - info->xmit_cnt - 1;
	return ret < 0 ? 0 : ret;
}

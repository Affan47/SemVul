write_room(struct tty_struct *tty)
{
	struct slgt_info *info = tty->driver_data;
	int ret;

	if (sanity_check(info, tty->name, "write_room"))
		return 0;
	ret = (info->tx_active) ? 0 : HDLC_MAX_FRAME_SIZE;
	DBGINFO(("%s write_room=%d\n", info->device_name, ret));
	return ret;
}

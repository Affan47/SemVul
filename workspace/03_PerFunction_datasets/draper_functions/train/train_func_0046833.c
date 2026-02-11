mgsl_write_room(struct tty_struct *tty)
{
	struct mgsl_struct *info = tty->driver_data;
	int	ret;

	if (mgsl_paranoia_check(info, tty->name, "mgsl_write_room"))
		return 0;
	ret = SERIAL_XMIT_SIZE - info->xmit_cnt - 1;
	if (ret < 0)
		ret = 0;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_write_room(%s)=%d\n",
			 __FILE__,__LINE__, info->device_name,ret );

	if ( info->params.mode == MGSL_MODE_HDLC ||
		info->params.mode == MGSL_MODE_RAW ) {

		if ( info->tx_active )
			return 0;
		else
			return HDLC_MAX_FRAME_SIZE;
	}

	return ret;

}

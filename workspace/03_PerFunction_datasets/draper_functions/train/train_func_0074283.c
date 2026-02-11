wait_until_sent(struct tty_struct *tty, int timeout)
{
	SLMP_INFO * info = tty->driver_data;
	unsigned long orig_jiffies, char_time;

	if (!info )
		return;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s wait_until_sent() entry\n",
			 __FILE__,__LINE__, info->device_name );

	if (sanity_check(info, tty->name, "wait_until_sent"))
		return;

	if (!test_bit(ASYNCB_INITIALIZED, &info->port.flags))
		goto exit;

	orig_jiffies = jiffies;


	if ( info->params.data_rate ) {
	       	char_time = info->timeout/(32 * 5);
		if (!char_time)
			char_time++;
	} else
		char_time = 1;

	if (timeout)
		char_time = min_t(unsigned long, char_time, timeout);

	if ( info->params.mode == MGSL_MODE_HDLC ) {
		while (info->tx_active) {
			msleep_interruptible(jiffies_to_msecs(char_time));
			if (signal_pending(current))
				break;
			if (timeout && time_after(jiffies, orig_jiffies + timeout))
				break;
		}
	} else {


		while ( info->tx_active && info->tx_enabled) {
			msleep_interruptible(jiffies_to_msecs(char_time));
			if (signal_pending(current))
				break;
			if (timeout && time_after(jiffies, orig_jiffies + timeout))
				break;
		}
	}

exit:
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s wait_until_sent() exit\n",
			 __FILE__,__LINE__, info->device_name );
}

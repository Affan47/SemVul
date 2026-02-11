pcipcwd_ioctl(struct file *file, unsigned int cmd,
						unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	int __user *p = argp;
	static const struct watchdog_info ident = {
		.options =		WDIOF_OVERHEAT |
					WDIOF_CARDRESET |
					WDIOF_KEEPALIVEPING |
					WDIOF_SETTIMEOUT |
					WDIOF_MAGICCLOSE,
		.firmware_version =	1,
		.identity =		WATCHDOG_DRIVER_NAME,
	};

	switch (cmd) {
	case WDIOC_GETSUPPORT:
		return copy_to_user(argp, &ident, sizeof(ident)) ? -EFAULT : 0;

	case WDIOC_GETSTATUS:
	{
		int status;
		pcipcwd_get_status(&status);
		return put_user(status, p);
	}

	case WDIOC_GETBOOTSTATUS:
		return put_user(pcipcwd_private.boot_status, p);

	case WDIOC_GETTEMP:
	{
		int temperature;

		if (pcipcwd_get_temperature(&temperature))
			return -EFAULT;

		return put_user(temperature, p);
	}

	case WDIOC_SETOPTIONS:
	{
		int new_options, retval = -EINVAL;

		if (get_user(new_options, p))
			return -EFAULT;

		if (new_options & WDIOS_DISABLECARD) {
			if (pcipcwd_stop())
				return -EIO;
			retval = 0;
		}

		if (new_options & WDIOS_ENABLECARD) {
			if (pcipcwd_start())
				return -EIO;
			retval = 0;
		}

		if (new_options & WDIOS_TEMPPANIC) {
			temp_panic = 1;
			retval = 0;
		}

		return retval;
	}

	case WDIOC_KEEPALIVE:
		pcipcwd_keepalive();
		return 0;

	case WDIOC_SETTIMEOUT:
	{
		int new_heartbeat;

		if (get_user(new_heartbeat, p))
			return -EFAULT;

		if (pcipcwd_set_heartbeat(new_heartbeat))
			return -EINVAL;

		pcipcwd_keepalive();

	}

	case WDIOC_GETTIMEOUT:
		return put_user(heartbeat, p);

	case WDIOC_GETTIMELEFT:
	{
		int time_left;

		if (pcipcwd_get_timeleft(&time_left))
			return -EFAULT;

		return put_user(time_left, p);
	}

	default:
		return -ENOTTY;
	}
}

fop_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	int __user *p = argp;
	static const struct watchdog_info ident = {
		.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT
							| WDIOF_MAGICCLOSE,
		.firmware_version = 1,
		.identity = "ALiM7101",
	};

	switch (cmd) {
	case WDIOC_GETSUPPORT:
		return copy_to_user(argp, &ident, sizeof(ident)) ? -EFAULT : 0;
	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		return put_user(0, p);
	case WDIOC_SETOPTIONS:
	{
		int new_options, retval = -EINVAL;

		if (get_user(new_options, p))
			return -EFAULT;
		if (new_options & WDIOS_DISABLECARD) {
			wdt_turnoff();
			retval = 0;
		}
		if (new_options & WDIOS_ENABLECARD) {
			wdt_startup();
			retval = 0;
		}
		return retval;
	}
	case WDIOC_KEEPALIVE:
		wdt_keepalive();
		return 0;
	case WDIOC_SETTIMEOUT:
	{
		int new_timeout;

		if (get_user(new_timeout, p))
			return -EFAULT;

		if (new_timeout < 1 || new_timeout > 3600)
			return -EINVAL;
		timeout = new_timeout;
		wdt_keepalive();

	}
	case WDIOC_GETTIMEOUT:
		return put_user(timeout, p);
	default:
		return -ENOTTY;
	}
}

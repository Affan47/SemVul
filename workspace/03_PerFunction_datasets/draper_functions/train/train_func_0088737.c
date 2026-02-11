eurwdt_ioctl(struct file *file,
					unsigned int cmd, unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	int __user *p = argp;
	static const struct watchdog_info ident = {
		.options	  = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT
							| WDIOF_MAGICCLOSE,
		.firmware_version = 1,
		.identity	  = "WDT Eurotech CPU-1220/1410",
	};

	int time;
	int options, retval = -EINVAL;

	switch (cmd) {
	case WDIOC_GETSUPPORT:
		return copy_to_user(argp, &ident, sizeof(ident)) ? -EFAULT : 0;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		return put_user(0, p);

	case WDIOC_SETOPTIONS:
		if (get_user(options, p))
			return -EFAULT;
		spin_lock(&eurwdt_lock);
		if (options & WDIOS_DISABLECARD) {
			eurwdt_disable_timer();
			retval = 0;
		}
		if (options & WDIOS_ENABLECARD) {
			eurwdt_activate_timer();
			eurwdt_ping();
			retval = 0;
		}
		spin_unlock(&eurwdt_lock);
		return retval;

	case WDIOC_KEEPALIVE:
		spin_lock(&eurwdt_lock);
		eurwdt_ping();
		spin_unlock(&eurwdt_lock);
		return 0;

	case WDIOC_SETTIMEOUT:
		if (copy_from_user(&time, p, sizeof(int)))
			return -EFAULT;


		if (time < 0 || time > 255)
			return -EINVAL;

		spin_lock(&eurwdt_lock);
		eurwdt_timeout = time;
		eurwdt_set_timeout(time);
		spin_unlock(&eurwdt_lock);


	case WDIOC_GETTIMEOUT:
		return put_user(eurwdt_timeout, p);

	default:
		return -ENOTTY;
	}
}

kempld_wdt_ioctl(struct watchdog_device *wdd, unsigned int cmd,
				unsigned long arg)
{
	struct kempld_wdt_data *wdt_data = watchdog_get_drvdata(wdd);
	void __user *argp = (void __user *)arg;
	int ret = -ENOIOCTLCMD;
	int __user *p = argp;
	int new_value;

	switch (cmd) {
	case WDIOC_SETPRETIMEOUT:
		if (get_user(new_value, p))
			return -EFAULT;
		ret = kempld_wdt_set_pretimeout(wdd, new_value);
		if (ret)
			return ret;
		ret = kempld_wdt_keepalive(wdd);
		break;
	case WDIOC_GETPRETIMEOUT:
		ret = put_user(wdt_data->pretimeout, (int __user *)arg);
		break;
	}

	return ret;
}

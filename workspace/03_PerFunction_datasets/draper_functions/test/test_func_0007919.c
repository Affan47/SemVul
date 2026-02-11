wafwdt_init(void)
{
	int ret;

	pr_info("WDT driver for Wafer 5823 single board computer initialising\n");

	if (timeout < 1 || timeout > 255) {
		timeout = WD_TIMO;
		pr_info("timeout value must be 1 <= x <= 255, using %d\n",
			timeout);
	}

	if (wdt_stop != wdt_start) {
		if (!request_region(wdt_stop, 1, "Wafer 5823 WDT")) {
			pr_err("I/O address 0x%04x already in use\n", wdt_stop);
			ret = -EIO;
			goto error;
		}
	}

	if (!request_region(wdt_start, 1, "Wafer 5823 WDT")) {
		pr_err("I/O address 0x%04x already in use\n", wdt_start);
		ret = -EIO;
		goto error2;
	}

	ret = register_reboot_notifier(&wafwdt_notifier);
	if (ret != 0) {
		pr_err("cannot register reboot notifier (err=%d)\n", ret);
		goto error3;
	}

	ret = misc_register(&wafwdt_miscdev);
	if (ret != 0) {
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
		goto error4;
	}

	pr_info("initialized. timeout=%d sec (nowayout=%d)\n",
		timeout, nowayout);

	return ret;
error4:
	unregister_reboot_notifier(&wafwdt_notifier);
error3:
	release_region(wdt_start, 1);
error2:
	if (wdt_stop != wdt_start)
		release_region(wdt_stop, 1);
error:
	return ret;
}

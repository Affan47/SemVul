watchdog_dev_register(struct watchdog_device *wdd)
{
	int err, devno;

	if (wdd->id == 0) {
		old_wdd = wdd;
		watchdog_miscdev.parent = wdd->parent;
		err = misc_register(&watchdog_miscdev);
		if (err != 0) {
			pr_err("%s: cannot register miscdev on minor=%d (err=%d).\n",
				wdd->info->identity, WATCHDOG_MINOR, err);
			if (err == -EBUSY)
				pr_err("%s: a legacy watchdog module is probably present.\n",
					wdd->info->identity);
			old_wdd = NULL;
			return err;
		}
	}


	devno = MKDEV(MAJOR(watchdog_devt), wdd->id);
	cdev_init(&wdd->cdev, &watchdog_fops);
	wdd->cdev.owner = wdd->ops->owner;


	err  = cdev_add(&wdd->cdev, devno, 1);
	if (err) {
		pr_err("watchdog%d unable to add device %d:%d\n",
			wdd->id,  MAJOR(watchdog_devt), wdd->id);
		if (wdd->id == 0) {
			misc_deregister(&watchdog_miscdev);
			old_wdd = NULL;
		}
	}
	return err;
}

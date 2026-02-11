usb_init(void)
{
	int r;

	pr_debug("%s usb_init()\n", driver.name);

	zd_workqueue = create_singlethread_workqueue(driver.name);
	if (zd_workqueue == NULL) {
		printk(KERN_ERR "%s couldn't create workqueue\n", driver.name);
		return -ENOMEM;
	}

	r = usb_register(&driver);
	if (r) {
		destroy_workqueue(zd_workqueue);
		printk(KERN_ERR "%s usb_register() failed. Error number %d\n",
		       driver.name, r);
		return r;
	}

	pr_debug("%s initialized\n", driver.name);
	return 0;
}

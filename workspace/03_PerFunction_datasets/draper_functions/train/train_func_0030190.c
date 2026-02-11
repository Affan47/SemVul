dgnc_start(void)
{
	int rc = 0;
	unsigned long flags;
	struct device *dev;


	init_timer(&dgnc_poll_timer);


	rc = register_chrdev(0, "dgnc", &dgnc_BoardFops);
	if (rc < 0) {
		pr_err(DRVSTR ": Can't register dgnc driver device (%d)\n", rc);
		return rc;
	}
	dgnc_Major = rc;

	dgnc_class = class_create(THIS_MODULE, "dgnc_mgmt");
	if (IS_ERR(dgnc_class)) {
		rc = PTR_ERR(dgnc_class);
		pr_err(DRVSTR ": Can't create dgnc_mgmt class (%d)\n", rc);
		goto failed_class;
	}

	dev = device_create(dgnc_class, NULL,
			    MKDEV(dgnc_Major, 0),
			NULL, "dgnc_mgmt");
	if (IS_ERR(dev)) {
		rc = PTR_ERR(dev);
		pr_err(DRVSTR ": Can't create device (%d)\n", rc);
		goto failed_device;
	}


	rc = dgnc_tty_preinit();

	if (rc < 0) {
		pr_err(DRVSTR ": tty preinit - not enough memory (%d)\n", rc);
		goto failed_tty;
	}


	spin_lock_irqsave(&dgnc_poll_lock, flags);
	setup_timer(&dgnc_poll_timer, dgnc_poll_handler, 0);
	dgnc_poll_time = jiffies + dgnc_jiffies_from_ms(dgnc_poll_tick);
	dgnc_poll_timer.expires = dgnc_poll_time;
	spin_unlock_irqrestore(&dgnc_poll_lock, flags);

	add_timer(&dgnc_poll_timer);

	return 0;

failed_tty:
	device_destroy(dgnc_class, MKDEV(dgnc_Major, 0));
failed_device:
	class_destroy(dgnc_class);
failed_class:
	unregister_chrdev(dgnc_Major, "dgnc");
	return rc;
}

ser_gigaset_init(void)
{
	int rc;

	gig_dbg(DEBUG_INIT, "%s", __func__);
	rc = platform_driver_register(&device_driver);
	if (rc != 0) {
		pr_err("error %d registering platform driver\n", rc);
		return rc;
	}


	driver = gigaset_initdriver(GIGASET_MINOR, GIGASET_MINORS,
				    GIGASET_MODULENAME, GIGASET_DEVNAME,
				    &ops, THIS_MODULE);
	if (!driver) {
		rc = -ENOMEM;
		goto error;
	}

	rc = tty_register_ldisc(N_GIGASET_M101, &gigaset_ldisc);
	if (rc != 0) {
		pr_err("error %d registering line discipline\n", rc);
		goto error;
	}

	return 0;

error:
	if (driver) {
		gigaset_freedriver(driver);
		driver = NULL;
	}
	platform_driver_unregister(&device_driver);
	return rc;
}

vt1211_init(void)
{
	int err;
	unsigned short address = 0;

	err = vt1211_find(SIO_REG_CIP1, &address);
	if (err) {
		err = vt1211_find(SIO_REG_CIP2, &address);
		if (err)
			goto EXIT;
	}

	if ((uch_config < -1) || (uch_config > 31)) {
		err = -EINVAL;
		pr_warn("Invalid UCH configuration %d. Choose a value between 0 and 31.\n",
			uch_config);
		goto EXIT;
	}

	if ((int_mode < -1) || (int_mode > 0)) {
		err = -EINVAL;
		pr_warn("Invalid interrupt mode %d. Only mode 0 is supported.\n",
			int_mode);
		goto EXIT;
	}

	err = platform_driver_register(&vt1211_driver);
	if (err)
		goto EXIT;


	err = vt1211_device_add(address);
	if (err)
		goto EXIT_DRV_UNREGISTER;

	return 0;

EXIT_DRV_UNREGISTER:
	platform_driver_unregister(&vt1211_driver);
EXIT:
	return err;
}

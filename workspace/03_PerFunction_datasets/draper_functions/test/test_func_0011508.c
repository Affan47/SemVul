dme1737_init(void)
{
	int err;
	unsigned short addr;

	err = i2c_add_driver(&dme1737_i2c_driver);
	if (err)
		goto exit;

	if (dme1737_isa_detect(0x2e, &addr) &&
	    dme1737_isa_detect(0x4e, &addr) &&
	    (!probe_all_addr ||
	     (dme1737_isa_detect(0x162e, &addr) &&
	      dme1737_isa_detect(0x164e, &addr)))) {

		return 0;
	}

	err = platform_driver_register(&dme1737_isa_driver);
	if (err)
		goto exit_del_i2c_driver;


	err = dme1737_isa_device_add(addr);
	if (err)
		goto exit_del_isa_driver;

	return 0;

exit_del_isa_driver:
	platform_driver_unregister(&dme1737_isa_driver);
exit_del_i2c_driver:
	i2c_del_driver(&dme1737_i2c_driver);
exit:
	return err;
}

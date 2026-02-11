infinipath_init(void)
{
	int ret;

	if (ipath_debug & __IPATH_DBG)
		printk(KERN_INFO DRIVER_LOAD_MSG "%s", ib_ipath_version);


	idr_init(&unit_table);

	ret = pci_register_driver(&ipath_driver);
	if (ret < 0) {
		printk(KERN_ERR IPATH_DRV_NAME
		       ": Unable to register driver: error %d\n", -ret);
		goto bail_unit;
	}

	ret = ipath_init_ipathfs();
	if (ret < 0) {
		printk(KERN_ERR IPATH_DRV_NAME ": Unable to create "
		       "ipathfs: error %d\n", -ret);
		goto bail_pci;
	}

	goto bail;

bail_pci:
	pci_unregister_driver(&ipath_driver);

bail_unit:
	idr_destroy(&unit_table);

bail:
	return ret;
}

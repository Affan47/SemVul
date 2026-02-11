register_ibdev ( struct ib_device *ibdev ) {
	struct ib_driver *driver;
	int rc;


	ibdev_get ( ibdev );
	list_add_tail ( &ibdev->list, &ib_devices );
	DBGC ( ibdev, "IBDEV %p registered (phys %s)\n", ibdev,
	       ibdev->dev->name );


	for_each_table_entry ( driver, IB_DRIVERS ) {
		if ( ( rc = driver->probe ( ibdev ) ) != 0 ) {
			DBGC ( ibdev, "IBDEV %p could not add %s device: %s\n",
			       ibdev, driver->name, strerror ( rc ) );
			goto err_probe;
		}
	}

	return 0;

 err_probe:
	for_each_table_entry_continue_reverse ( driver, IB_DRIVERS )
		driver->remove ( ibdev );
	list_del ( &ibdev->list );
	ibdev_put ( ibdev );
	return rc;
}

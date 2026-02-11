fwserial_exit(void)
{
	driver_unregister(&fwserial_driver.driver);
	fw_core_remove_descriptor(&fwserial_unit_directory);
	fw_core_remove_address_handler(&fwserial_mgmt_addr_handler);
	kmem_cache_destroy(fwtty_txn_cache);
	if (create_loop_dev) {
		tty_unregister_driver(fwloop_driver);
		put_tty_driver(fwloop_driver);
	}
	tty_unregister_driver(fwtty_driver);
	put_tty_driver(fwtty_driver);
	debugfs_remove_recursive(fwserial_debugfs);
}

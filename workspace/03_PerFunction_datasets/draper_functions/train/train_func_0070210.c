register_virtio_driver(struct virtio_driver *driver)
{

	BUG_ON(driver->feature_table_size && !driver->feature_table);
	driver->driver.bus = &virtio_bus;
	return driver_register(&driver->driver);
}

mipi_dsi_driver_register_full(struct mipi_dsi_driver *drv,
				  struct module *owner)
{
	drv->driver.bus = &mipi_dsi_bus_type;
	drv->driver.owner = owner;

	if (drv->probe)
		drv->driver.probe = mipi_dsi_drv_probe;
	if (drv->remove)
		drv->driver.remove = mipi_dsi_drv_remove;
	if (drv->shutdown)
		drv->driver.shutdown = mipi_dsi_drv_shutdown;

	return driver_register(&drv->driver);
}

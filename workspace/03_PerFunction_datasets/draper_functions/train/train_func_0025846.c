resume_iter(struct device *dev, void *data)
{
	struct pcie_port_service_driver *service_driver;

	if ((dev->bus == &pcie_port_bus_type) &&
	    (dev->driver)) {
		service_driver = to_service_driver(dev->driver);
		if (service_driver->resume)
			service_driver->resume(to_pcie_device(dev));
	}
	return 0;
}

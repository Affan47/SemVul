pci_reset_notify(struct pci_dev *dev, bool prepare)
{
	const struct pci_error_handlers *err_handler =
			dev->driver ? dev->driver->err_handler : NULL;
	if (err_handler && err_handler->reset_notify)
		err_handler->reset_notify(dev, prepare);
}

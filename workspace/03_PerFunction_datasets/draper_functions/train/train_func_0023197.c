acpi_video_bus_check(struct acpi_video_bus *video)
{
	acpi_status status = -ENOENT;
	struct pci_dev *dev;

	if (!video)
		return -EINVAL;

	dev = acpi_get_pci_dev(video->device->handle);
	if (!dev)
		return -ENODEV;
	pci_dev_put(dev);


	if (video->cap._DOS || video->cap._DOD) {
		if (!video->cap._DOS) {
			printk(KERN_WARNING FW_BUG
				"ACPI(%s) defines _DOD but not _DOS\n",
				acpi_device_bid(video->device));
		}
		video->flags.multihead = 1;
		status = 0;
	}


	if (video->cap._ROM) {
		video->flags.rom = 1;
		status = 0;
	}


	if (video->cap._GPD && video->cap._SPD && video->cap._VPO) {
		video->flags.post = 1;
		status = 0;
	}

	return status;
}

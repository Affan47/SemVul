acpi_video_device_find_cap(struct acpi_video_device *device)
{
	if (acpi_has_method(device->dev->handle, "_ADR"))
		device->cap._ADR = 1;
	if (acpi_has_method(device->dev->handle, "_BCL"))
		device->cap._BCL = 1;
	if (acpi_has_method(device->dev->handle, "_BCM"))
		device->cap._BCM = 1;
	if (acpi_has_method(device->dev->handle, "_BQC")) {
		device->cap._BQC = 1;
	} else if (acpi_has_method(device->dev->handle, "_BCQ")) {
		printk(KERN_WARNING FW_BUG "_BCQ is used instead of _BQC\n");
		device->cap._BCQ = 1;
	}

	if (acpi_has_method(device->dev->handle, "_DDC"))
		device->cap._DDC = 1;
}

acpi_video_dev_remove_notify_handler(struct acpi_video_device *dev)
{
	if (dev->flags.notify) {
		acpi_remove_notify_handler(dev->dev->handle, ACPI_DEVICE_NOTIFY,
					   acpi_video_device_notify);
		dev->flags.notify = 0;
	}
}

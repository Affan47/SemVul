acpi_video_dev_add_notify_handler(struct acpi_video_device *device)
{
	acpi_status status;
	struct acpi_device *adev = device->dev;

	status = acpi_install_notify_handler(adev->handle, ACPI_DEVICE_NOTIFY,
					     acpi_video_device_notify, device);
	if (ACPI_FAILURE(status))
		dev_err(&adev->dev, "Error installing notify handler\n");
	else
		device->flags.notify = 1;
}

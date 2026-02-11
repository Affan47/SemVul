acpi_video_bus_remove(struct acpi_device *device)
{
	struct acpi_video_bus *video = NULL;


	if (!device || !acpi_driver_data(device))
		return -EINVAL;

	video = acpi_driver_data(device);

	acpi_video_bus_remove_notify_handler(video);
	acpi_video_bus_unregister_backlight(video);
	acpi_video_bus_put_devices(video);

	mutex_lock(&video_list_lock);
	list_del(&video->entry);
	mutex_unlock(&video_list_lock);

	kfree(video->attached_array);
	kfree(video);

	return 0;
}

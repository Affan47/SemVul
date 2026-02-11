acpi_wakeup_device_init(void)
{
	struct list_head *node, *next;

	mutex_lock(&acpi_device_lock);
	list_for_each_safe(node, next, &acpi_wakeup_device_list) {
		struct acpi_device *dev = container_of(node,
						       struct acpi_device,
						       wakeup_list);
		if (device_can_wakeup(&dev->dev)) {

			acpi_enable_gpe(dev->wakeup.gpe_device,
					dev->wakeup.gpe_number);
			device_set_wakeup_enable(&dev->dev, true);
		}
	}
	mutex_unlock(&acpi_device_lock);
	return 0;
}

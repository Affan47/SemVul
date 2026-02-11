acpi_i2c_add_device(acpi_handle handle, u32 level,
				       void *data, void **return_value)
{
	struct i2c_adapter *adapter = data;
	struct list_head resource_list;
	struct acpi_i2c_lookup lookup;
	struct resource_entry *entry;
	struct i2c_board_info info;
	struct acpi_device *adev;
	int ret;

	if (acpi_bus_get_device(handle, &adev))
		return AE_OK;
	if (acpi_bus_get_status(adev) || !adev->status.present)
		return AE_OK;

	memset(&info, 0, sizeof(info));
	info.fwnode = acpi_fwnode_handle(adev);

	memset(&lookup, 0, sizeof(lookup));
	lookup.adapter_handle = ACPI_HANDLE(&adapter->dev);
	lookup.device_handle = handle;
	lookup.info = &info;


	INIT_LIST_HEAD(&resource_list);
	ret = acpi_dev_get_resources(adev, &resource_list,
				     acpi_i2c_find_address, &lookup);
	acpi_dev_free_resource_list(&resource_list);

	if (ret < 0 || !info.addr)
		return AE_OK;


	ret = acpi_dev_get_resources(adev, &resource_list, NULL, NULL);
	if (ret < 0)
		return AE_OK;

	resource_list_for_each_entry(entry, &resource_list) {
		if (resource_type(entry->res) == IORESOURCE_IRQ) {
			info.irq = entry->res->start;
			break;
		}
	}

	acpi_dev_free_resource_list(&resource_list);

	adev->power.flags.ignore_parent = true;
	strlcpy(info.type, dev_name(&adev->dev), sizeof(info.type));
	if (!i2c_new_device(adapter, &info)) {
		adev->power.flags.ignore_parent = false;
		dev_err(&adapter->dev,
			"failed to add I2C device %s from ACPI\n",
			dev_name(&adev->dev));
	}

	return AE_OK;
}

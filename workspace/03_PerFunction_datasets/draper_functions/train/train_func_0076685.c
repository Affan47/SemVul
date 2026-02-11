i2c_hid_acpi_pdata(struct i2c_client *client,
		struct i2c_hid_platform_data *pdata)
{
	static u8 i2c_hid_guid[] = {
		0xF7, 0xF6, 0xDF, 0x3C, 0x67, 0x42, 0x55, 0x45,
		0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE,
	};
	union acpi_object *obj;
	struct acpi_device *adev;
	acpi_handle handle;
	int ret;

	handle = ACPI_HANDLE(&client->dev);
	if (!handle || acpi_bus_get_device(handle, &adev))
		return -ENODEV;

	obj = acpi_evaluate_dsm_typed(handle, i2c_hid_guid, 1, 1, NULL,
				      ACPI_TYPE_INTEGER);
	if (!obj) {
		dev_err(&client->dev, "device _DSM execution failed\n");
		return -ENODEV;
	}

	pdata->hid_descriptor_address = obj->integer.value;
	ACPI_FREE(obj);


	ret = acpi_dev_add_driver_gpios(adev, i2c_hid_acpi_gpios);
	return ret < 0 && ret != -ENXIO ? ret : 0;
}

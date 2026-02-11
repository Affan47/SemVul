acpi_smbus_cmi_add(struct acpi_device *device)
{
	struct acpi_smbus_cmi *smbus_cmi;
	const struct acpi_device_id *id;

	smbus_cmi = kzalloc(sizeof(struct acpi_smbus_cmi), GFP_KERNEL);
	if (!smbus_cmi)
		return -ENOMEM;

	smbus_cmi->handle = device->handle;
	strcpy(acpi_device_name(device), ACPI_SMBUS_HC_DEVICE_NAME);
	strcpy(acpi_device_class(device), ACPI_SMBUS_HC_CLASS);
	device->driver_data = smbus_cmi;
	smbus_cmi->cap_info = 0;
	smbus_cmi->cap_read = 0;
	smbus_cmi->cap_write = 0;

	for (id = acpi_smbus_cmi_ids; id->id[0]; id++)
		if (!strcmp(id->id, acpi_device_hid(device)))
			smbus_cmi->methods =
				(struct smbus_methods_t *) id->driver_data;

	acpi_walk_namespace(ACPI_TYPE_METHOD, smbus_cmi->handle, 1,
			    acpi_smbus_cmi_query_methods, NULL, smbus_cmi, NULL);

	if (smbus_cmi->cap_info == 0)
		goto err;

	snprintf(smbus_cmi->adapter.name, sizeof(smbus_cmi->adapter.name),
		"SMBus CMI adapter %s",
		acpi_device_name(device));
	smbus_cmi->adapter.owner = THIS_MODULE;
	smbus_cmi->adapter.algo = &acpi_smbus_cmi_algorithm;
	smbus_cmi->adapter.algo_data = smbus_cmi;
	smbus_cmi->adapter.class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	smbus_cmi->adapter.dev.parent = &device->dev;

	if (i2c_add_adapter(&smbus_cmi->adapter)) {
		dev_err(&device->dev, "Couldn't register adapter!\n");
		goto err;
	}

	return 0;

err:
	kfree(smbus_cmi);
	device->driver_data = NULL;
	return -EIO;
}

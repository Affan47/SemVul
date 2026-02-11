acpi_device_setup_files(struct acpi_device *dev)
{
	struct acpi_buffer buffer = {ACPI_ALLOCATE_BUFFER, NULL};
	acpi_status status;
	int result = 0;


	if (dev->handle) {
		result = device_create_file(&dev->dev, &dev_attr_path);
		if (result)
			goto end;
	}

	if (!list_empty(&dev->pnp.ids)) {
		result = device_create_file(&dev->dev, &dev_attr_hid);
		if (result)
			goto end;

		result = device_create_file(&dev->dev, &dev_attr_modalias);
		if (result)
			goto end;
	}


	if (acpi_has_method(dev->handle, "_STR")) {
		status = acpi_evaluate_object(dev->handle, "_STR",
					NULL, &buffer);
		if (ACPI_FAILURE(status))
			buffer.pointer = NULL;
		dev->pnp.str_obj = buffer.pointer;
		result = device_create_file(&dev->dev, &dev_attr_description);
		if (result)
			goto end;
	}

	if (dev->pnp.type.bus_address)
		result = device_create_file(&dev->dev, &dev_attr_adr);
	if (dev->pnp.unique_id)
		result = device_create_file(&dev->dev, &dev_attr_uid);

	if (acpi_has_method(dev->handle, "_SUN")) {
		result = device_create_file(&dev->dev, &dev_attr_sun);
		if (result)
			goto end;
	}

	if (acpi_has_method(dev->handle, "_STA")) {
		result = device_create_file(&dev->dev, &dev_attr_status);
		if (result)
			goto end;
	}


	if (acpi_has_method(dev->handle, "_EJ0")) {
		result = device_create_file(&dev->dev, &dev_attr_eject);
		if (result)
			return result;
	}

	if (dev->flags.power_manageable) {
		result = device_create_file(&dev->dev, &dev_attr_power_state);
		if (result)
			return result;

		if (dev->power.flags.power_resources)
			result = device_create_file(&dev->dev,
						    &dev_attr_real_power_state);
	}

	acpi_expose_nondev_subnodes(&dev->dev.kobj, &dev->data);

end:
	return result;
}

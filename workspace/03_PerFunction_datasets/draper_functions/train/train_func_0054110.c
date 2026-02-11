acpi_ec_add(struct acpi_device *device)
{
	struct acpi_ec *ec = NULL;
	int ret;

	strcpy(acpi_device_name(device), ACPI_EC_DEVICE_NAME);
	strcpy(acpi_device_class(device), ACPI_EC_CLASS);


	if (boot_ec &&
	    (boot_ec->handle == device->handle ||
	     boot_ec->handle == ACPI_ROOT_OBJECT)) {
		ec = boot_ec;
		boot_ec = NULL;
	} else {
		ec = make_acpi_ec();
		if (!ec)
			return -ENOMEM;
	}
	if (ec_parse_device(device->handle, 0, ec, NULL) !=
		AE_CTRL_TERMINATE) {
			kfree(ec);
			return -EINVAL;
	}


	acpi_walk_namespace(ACPI_TYPE_METHOD, ec->handle, 1,
			    acpi_ec_register_query_methods, NULL, ec, NULL);

	if (!first_ec)
		first_ec = ec;
	device->driver_data = ec;

	ret = !!request_region(ec->data_addr, 1, "EC data");
	WARN(!ret, "Could not request EC data io port 0x%lx", ec->data_addr);
	ret = !!request_region(ec->command_addr, 1, "EC cmd");
	WARN(!ret, "Could not request EC cmd io port 0x%lx", ec->command_addr);

	pr_info("GPE = 0x%lx, I/O: command/status = 0x%lx, data = 0x%lx\n",
			  ec->gpe, ec->command_addr, ec->data_addr);

	ret = ec_install_handlers(ec);


	acpi_walk_dep_device_list(ec->handle);


	clear_bit(EC_FLAGS_QUERY_PENDING, &ec->flags);


	if (EC_FLAGS_CLEAR_ON_RESUME)
		acpi_ec_clear(ec);
	return ret;
}

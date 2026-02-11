acpi_dev_resource_address_space(struct acpi_resource *ares,
				     struct resource_win *win)
{
	struct acpi_resource_address64 addr;

	win->res.flags = 0;
	if (ACPI_FAILURE(acpi_resource_to_address64(ares, &addr)))
		return false;

	return acpi_decode_space(win, (struct acpi_resource_address *)&addr,
				 &addr.address);
}

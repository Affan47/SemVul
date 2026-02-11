crb_check_resource(struct acpi_resource *ares, void *data)
{
	struct resource *io_res = data;
	struct resource res;

	if (acpi_dev_resource_memory(ares, &res)) {
		*io_res = res;
		io_res->name = NULL;
	}

	return 1;
}

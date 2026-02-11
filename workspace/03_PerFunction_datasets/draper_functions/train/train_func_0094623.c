acpi_memory_get_device_resources(struct acpi_memory_device *mem_device)
{
	acpi_status status;

	if (!list_empty(&mem_device->res_list))
		return 0;

	status = acpi_walk_resources(mem_device->device->handle, METHOD_NAME__CRS,
				     acpi_memory_get_resource, mem_device);
	if (ACPI_FAILURE(status)) {
		acpi_memory_free_device_resources(mem_device);
		return -EINVAL;
	}

	return 0;
}

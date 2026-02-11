acpi_dev_get_resources(struct acpi_device *adev, struct list_head *list,
			   int (*preproc)(struct acpi_resource *, void *),
			   void *preproc_data)
{
	struct res_proc_context c;
	acpi_status status;

	if (!adev || !adev->handle || !list_empty(list))
		return -EINVAL;

	if (!acpi_has_method(adev->handle, METHOD_NAME__CRS))
		return 0;

	c.list = list;
	c.preproc = preproc;
	c.preproc_data = preproc_data;
	c.count = 0;
	c.error = 0;
	status = acpi_walk_resources(adev->handle, METHOD_NAME__CRS,
				     acpi_dev_process_resource, &c);
	if (ACPI_FAILURE(status)) {
		acpi_dev_free_resource_list(list);
		return c.error ? c.error : -EIO;
	}

	return c.count;
}

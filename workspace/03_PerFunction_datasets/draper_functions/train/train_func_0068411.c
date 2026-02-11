acpi_db_walk_for_specific_objects(acpi_handle obj_handle,
				  u32 nesting_level,
				  void *context, void **return_value)
{
	struct acpi_walk_info *info = (struct acpi_walk_info *)context;
	struct acpi_buffer buffer;
	acpi_status status;

	info->count++;


	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	status = acpi_ns_handle_to_pathname(obj_handle, &buffer, TRUE);
	if (ACPI_FAILURE(status)) {
		acpi_os_printf("Could Not get pathname for object %p\n",
			       obj_handle);
		return (AE_OK);
	}

	acpi_os_printf("%32s", (char *)buffer.pointer);
	ACPI_FREE(buffer.pointer);


	(void)acpi_ns_dump_one_object(obj_handle, nesting_level, info, NULL);
	return (AE_OK);
}

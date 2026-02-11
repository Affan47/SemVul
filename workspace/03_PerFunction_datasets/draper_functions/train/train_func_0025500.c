acpi_release_mutex(acpi_handle handle, acpi_string pathname)
{
	acpi_status status;
	union acpi_operand_object *mutex_obj;


	status = acpi_ut_get_mutex_object(handle, pathname, &mutex_obj);
	if (ACPI_FAILURE(status)) {
		return (status);
	}


	acpi_os_release_mutex(mutex_obj->mutex.os_mutex);
	return (AE_OK);
}

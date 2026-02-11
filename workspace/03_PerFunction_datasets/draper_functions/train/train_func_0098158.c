asus_acpi_get_sensor_info(struct acpi_device *adev,
				     struct i2c_client *client,
				     struct i2c_board_info *info)
{
	struct acpi_buffer buffer = {ACPI_ALLOCATE_BUFFER, NULL};
	int i;
	acpi_status status;
	union acpi_object *cpm;

	status = acpi_evaluate_object(adev->handle, "CNF0", NULL, &buffer);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	cpm = buffer.pointer;
	for (i = 0; i < cpm->package.count; ++i) {
		union acpi_object *elem;
		int j;

		elem = &(cpm->package.elements[i]);
		for (j = 0; j < elem->package.count; ++j) {
			union acpi_object *sub_elem;

			sub_elem = &(elem->package.elements[j]);
			if (sub_elem->type == ACPI_TYPE_STRING)
				strlcpy(info->type, sub_elem->string.pointer,
					sizeof(info->type));
			else if (sub_elem->type == ACPI_TYPE_INTEGER) {
				if (sub_elem->integer.value != client->addr) {
					info->addr = sub_elem->integer.value;
					break;
				}
			}
		}
	}

	kfree(buffer.pointer);

	return cpm->package.count;
}

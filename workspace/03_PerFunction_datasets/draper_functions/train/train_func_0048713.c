sony_nc_buffer_call(acpi_handle handle, char *name, u64 *value,
		void *buffer, size_t buflen)
{
	int ret = 0;
	size_t len;
	union acpi_object *object = __call_snc_method(handle, name, value);

	if (!object)
		return -EINVAL;

	if (object->type == ACPI_TYPE_BUFFER) {
		len = MIN(buflen, object->buffer.length);
		memcpy(buffer, object->buffer.pointer, len);

	} else if (object->type == ACPI_TYPE_INTEGER) {
		len = MIN(buflen, sizeof(object->integer.value));
		memcpy(buffer, &object->integer.value, len);

	} else {
		pr_warn("Invalid acpi_object: expected 0x%x got 0x%x\n",
				ACPI_TYPE_BUFFER, object->type);
		ret = -EINVAL;
	}

	kfree(object);
	return ret;
}

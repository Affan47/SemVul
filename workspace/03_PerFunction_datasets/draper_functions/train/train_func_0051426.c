acpi_ns_convert_to_unicode(union acpi_operand_object *original_object,
			   union acpi_operand_object **return_object)
{
	union acpi_operand_object *new_object;
	char *ascii_string;
	u16 *unicode_buffer;
	u32 unicode_length;
	u32 i;

	if (!original_object) {
		return (AE_OK);
	}


	if (original_object->common.type == ACPI_TYPE_BUFFER) {
		if (original_object->buffer.length < 2) {
			return (AE_AML_OPERAND_VALUE);
		}

		*return_object = NULL;
		return (AE_OK);
	}


	ascii_string = original_object->string.pointer;
	unicode_length = (original_object->string.length * 2) + 2;


	new_object = acpi_ut_create_buffer_object(unicode_length);
	if (!new_object) {
		return (AE_NO_MEMORY);
	}

	unicode_buffer = ACPI_CAST_PTR(u16, new_object->buffer.pointer);


	for (i = 0; i < original_object->string.length; i++) {
		unicode_buffer[i] = (u16)ascii_string[i];
	}

	*return_object = new_object;
	return (AE_OK);
}

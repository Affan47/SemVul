acpi_ex_get_serial_access_length(u32 accessor_type, u32 access_length)
{
	u32 length;

	switch (accessor_type) {
	case AML_FIELD_ATTRIB_QUICK:

		length = 0;
		break;

	case AML_FIELD_ATTRIB_SEND_RCV:
	case AML_FIELD_ATTRIB_BYTE:

		length = 1;
		break;

	case AML_FIELD_ATTRIB_WORD:
	case AML_FIELD_ATTRIB_WORD_CALL:

		length = 2;
		break;

	case AML_FIELD_ATTRIB_MULTIBYTE:
	case AML_FIELD_ATTRIB_RAW_BYTES:
	case AML_FIELD_ATTRIB_RAW_PROCESS:

		length = access_length;
		break;

	case AML_FIELD_ATTRIB_BLOCK:
	case AML_FIELD_ATTRIB_BLOCK_CALL:
	default:

		length = ACPI_GSBUS_BUFFER_SIZE - 2;
		break;
	}

	return (length);
}

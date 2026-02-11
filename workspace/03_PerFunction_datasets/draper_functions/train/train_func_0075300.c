acpi_db_uint32_to_hex_string(u32 value, char *buffer)
{
	int i;

	if (value == 0) {
		strcpy(buffer, "0");
		return;
	}

	buffer[8] = '\0';

	for (i = 7; i >= 0; i--) {
		buffer[i] = gbl_hex_to_ascii[value & 0x0F];
		value = value >> 4;
	}
}

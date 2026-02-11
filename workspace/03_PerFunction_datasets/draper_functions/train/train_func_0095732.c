acpi_ut_repair_name(char *name)
{
	u32 i;
	u8 found_bad_char = FALSE;
	u32 original_name;

	ACPI_FUNCTION_NAME(ut_repair_name);

	ACPI_MOVE_NAME(&original_name, name);


	for (i = 0; i < ACPI_NAME_SIZE; i++) {
		if (acpi_ut_valid_acpi_char(name[i], i)) {
			continue;
		}


		name[i] = '*';
		found_bad_char = TRUE;
	}

	if (found_bad_char) {


		if (!acpi_gbl_enable_interpreter_slack) {
			ACPI_WARNING((AE_INFO,
				      "Invalid character(s) in name (0x%.8X), repaired: [%4.4s]",
				      original_name, name));
		} else {
			ACPI_DEBUG_PRINT((ACPI_DB_INFO,
					  "Invalid character(s) in name (0x%.8X), repaired: [%4.4s]",
					  original_name, name));
		}
	}
}

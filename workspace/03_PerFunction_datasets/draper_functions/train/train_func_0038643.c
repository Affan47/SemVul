acpi_tb_fix_string(char *string, acpi_size length)
{

	while (length && *string) {
		if (!isprint((int)*string)) {
			*string = '?';
		}
		string++;
		length--;
	}
}

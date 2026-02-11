acpi_db_disassemble_aml(char *statements, union acpi_parse_object *op)
{
	u32 num_statements = 8;

	if (!op) {
		acpi_os_printf("There is no method currently executing\n");
		return;
	}

	if (statements) {
		num_statements = strtoul(statements, NULL, 0);
	}
#ifdef ACPI_DISASSEMBLER
	acpi_dm_disassemble(NULL, op, num_statements);
#endif
}

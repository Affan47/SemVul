acpi_ex_dump_operands(union acpi_operand_object **operands,
		      const char *opcode_name, u32 num_operands)
{
	ACPI_FUNCTION_NAME(ex_dump_operands);

	if (!opcode_name) {
		opcode_name = "UNKNOWN";
	}

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "**** Start operand dump for opcode [%s], %u operands\n",
			  opcode_name, num_operands));

	if (num_operands == 0) {
		num_operands = 1;
	}


	while (num_operands) {
		acpi_ex_dump_operand(*operands, 0);
		operands++;
		num_operands--;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "**** End operand dump for [%s]\n", opcode_name));
	return;
}

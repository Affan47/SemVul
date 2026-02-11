print_arch(unsigned int value, int op)
{
	int machine;
	_audit_elf = value;
	machine = audit_elf_to_machine(_audit_elf);
	if (machine < 0)
		printf(" -F arch%s0x%X", audit_operator_to_symbol(op),
				(unsigned)value);
	else {
		const char *ptr = audit_machine_to_name(machine);
		printf(" -F arch%s%s", audit_operator_to_symbol(op), ptr);
	}
	return machine;
}

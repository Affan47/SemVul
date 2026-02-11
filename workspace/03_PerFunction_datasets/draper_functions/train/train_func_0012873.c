acpiphp_set_acpi_region(struct acpiphp_slot *slot)
{
	struct acpiphp_func *func;
	union acpi_object params[2];
	struct acpi_object_list arg_list;

	list_for_each_entry(func, &slot->funcs, sibling) {
		arg_list.count = 2;
		arg_list.pointer = params;
		params[0].type = ACPI_TYPE_INTEGER;
		params[0].integer.value = ACPI_ADR_SPACE_PCI_CONFIG;
		params[1].type = ACPI_TYPE_INTEGER;
		params[1].integer.value = 1;

		acpi_evaluate_object(func_to_handle(func), "_REG", &arg_list,
				     NULL);
	}
}

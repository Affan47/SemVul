acpi_parse_lapic(struct acpi_subtable_header * header, const unsigned long end)
{
	struct acpi_madt_local_apic *processor = NULL;

	processor = (struct acpi_madt_local_apic *)header;

	if (BAD_MADT_ENTRY(processor, end))
		return -EINVAL;

	acpi_table_print_madt_entry(header);


	acpi_register_lapic(processor->id,
			    processor->lapic_flags & ACPI_MADT_ENABLED);

	return 0;
}

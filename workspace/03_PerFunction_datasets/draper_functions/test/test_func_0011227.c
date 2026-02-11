acpi_ata_match(acpi_handle handle)
{
	return acpi_has_method(handle, "_GTF") ||
	       acpi_has_method(handle, "_GTM") ||
	       acpi_has_method(handle, "_STM") ||
	       acpi_has_method(handle, "_SDD");
}

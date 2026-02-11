map_gicc_mpidr(struct acpi_subtable_header *entry,
		int device_declaration, u32 acpi_id, phys_cpuid_t *mpidr)
{
	struct acpi_madt_generic_interrupt *gicc =
	    container_of(entry, struct acpi_madt_generic_interrupt, header);

	if (!(gicc->flags & ACPI_MADT_ENABLED))
		return -ENODEV;


	if (device_declaration && (gicc->uid == acpi_id)) {
		*mpidr = gicc->arm_mpidr;
		return 0;
	}

	return -EINVAL;
}

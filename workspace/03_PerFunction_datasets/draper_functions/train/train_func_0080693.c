dmar_acpi_dev_scope_init(void)
{
	struct acpi_dmar_andd *andd;

	if (dmar_tbl == NULL)
		return -ENODEV;

	for (andd = (void *)dmar_tbl + sizeof(struct acpi_table_dmar);
	     ((unsigned long)andd) < ((unsigned long)dmar_tbl) + dmar_tbl->length;
	     andd = ((void *)andd) + andd->header.length) {
		if (andd->header.type == ACPI_DMAR_TYPE_NAMESPACE) {
			acpi_handle h;
			struct acpi_device *adev;

			if (!ACPI_SUCCESS(acpi_get_handle(ACPI_ROOT_OBJECT,
							  andd->device_name,
							  &h))) {
				pr_err("Failed to find handle for ACPI object %s\n",
				       andd->device_name);
				continue;
			}
			if (acpi_bus_get_device(h, &adev)) {
				pr_err("Failed to get device for ACPI object %s\n",
				       andd->device_name);
				continue;
			}
			dmar_acpi_insert_dev_scope(andd->device_number, adev);
		}
	}
	return 0;
}

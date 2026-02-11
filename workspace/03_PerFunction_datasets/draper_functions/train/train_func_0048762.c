acpi_nfit_register_regions(struct acpi_nfit_desc *acpi_desc)
{
	struct nfit_spa *nfit_spa;

	list_for_each_entry(nfit_spa, &acpi_desc->spas, list) {
		int rc = acpi_nfit_register_region(acpi_desc, nfit_spa);

		if (rc)
			return rc;
	}
	return 0;
}

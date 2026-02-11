acpi_nfit_dimm_by_handle(struct acpi_nfit_desc *acpi_desc,
		u32 device_handle)
{
	struct nfit_mem *nfit_mem;

	list_for_each_entry(nfit_mem, &acpi_desc->dimms, list)
		if (__to_nfit_memdev(nfit_mem)->device_handle == device_handle)
			return nfit_mem->nvdimm;

	return NULL;
}

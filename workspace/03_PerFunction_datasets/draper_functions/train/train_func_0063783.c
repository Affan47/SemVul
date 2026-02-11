cper_estatus_print_section(
	const char *pfx, const struct acpi_hest_generic_data *gdata, int sec_no)
{
	uuid_le *sec_type = (uuid_le *)gdata->section_type;
	__u16 severity;
	char newpfx[64];

	severity = gdata->error_severity;
	printk("%s""Error %d, type: %s\n", pfx, sec_no,
	       cper_severity_str(severity));
	if (gdata->validation_bits & CPER_SEC_VALID_FRU_ID)
		printk("%s""fru_id: %pUl\n", pfx, (uuid_le *)gdata->fru_id);
	if (gdata->validation_bits & CPER_SEC_VALID_FRU_TEXT)
		printk("%s""fru_text: %.20s\n", pfx, gdata->fru_text);

	snprintf(newpfx, sizeof(newpfx), "%s%s", pfx, INDENT_SP);
	if (!uuid_le_cmp(*sec_type, CPER_SEC_PROC_GENERIC)) {
		struct cper_sec_proc_generic *proc_err = (void *)(gdata + 1);
		printk("%s""section_type: general processor error\n", newpfx);
		if (gdata->error_data_length >= sizeof(*proc_err))
			cper_print_proc_generic(newpfx, proc_err);
		else
			goto err_section_too_small;
	} else if (!uuid_le_cmp(*sec_type, CPER_SEC_PLATFORM_MEM)) {
		struct cper_sec_mem_err *mem_err = (void *)(gdata + 1);
		printk("%s""section_type: memory error\n", newpfx);
		if (gdata->error_data_length >=
		    sizeof(struct cper_sec_mem_err_old))
			cper_print_mem(newpfx, mem_err,
				       gdata->error_data_length);
		else
			goto err_section_too_small;
	} else if (!uuid_le_cmp(*sec_type, CPER_SEC_PCIE)) {
		struct cper_sec_pcie *pcie = (void *)(gdata + 1);
		printk("%s""section_type: PCIe error\n", newpfx);
		if (gdata->error_data_length >= sizeof(*pcie))
			cper_print_pcie(newpfx, pcie, gdata);
		else
			goto err_section_too_small;
	} else
		printk("%s""section type: unknown, %pUl\n", newpfx, sec_type);

	return;

err_section_too_small:
	pr_err(FW_WARN "error section length is too small\n");
}

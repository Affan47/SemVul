sfi_sysfs_init(void)
{
	int tbl_cnt, i;

	if (sfi_disabled)
		return 0;

	sfi_kobj = kobject_create_and_add("sfi", firmware_kobj);
	if (!sfi_kobj)
		return 0;

	tables_kobj = kobject_create_and_add("tables", sfi_kobj);
	if (!tables_kobj) {
		kobject_put(sfi_kobj);
		return 0;
	}

	sfi_sysfs_install_table(syst_pa);

	tbl_cnt = SFI_GET_NUM_ENTRIES(syst_va, u64);

	for (i = 0; i < tbl_cnt; i++)
		sfi_sysfs_install_table(syst_va->pentry[i]);

	sfi_acpi_sysfs_init();
	kobject_uevent(sfi_kobj, KOBJ_ADD);
	kobject_uevent(tables_kobj, KOBJ_ADD);
	pr_info("SFI sysfs interfaces init success\n");
	return 0;
}

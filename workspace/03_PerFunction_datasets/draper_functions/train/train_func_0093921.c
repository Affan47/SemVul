edac_pci_main_kobj_teardown(void)
{
	edac_dbg(0, "\n");


	if (atomic_dec_return(&edac_pci_sysfs_refcount) == 0) {
		edac_dbg(0, "called kobject_put on main kobj\n");
		kobject_put(edac_pci_top_main_kobj);
		edac_put_sysfs_subsys();
	}
}

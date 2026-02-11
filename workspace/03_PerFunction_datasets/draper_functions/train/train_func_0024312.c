edac_pci_unregister_sysfs_instance_kobj(
			struct edac_pci_ctl_info *pci)
{
	edac_dbg(0, "\n");


	kobject_put(&pci->kobj);
}

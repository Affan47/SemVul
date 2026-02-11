xen_has_pv_and_legacy_disk_devices(void)
{
	if (!xen_domain())
		return false;


	if (xen_pv_domain())
		return false;

	if (xen_platform_pci_unplug & XEN_UNPLUG_UNNECESSARY)
		return true;

	return false;
}

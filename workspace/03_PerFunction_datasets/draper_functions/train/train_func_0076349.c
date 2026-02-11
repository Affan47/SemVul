via_cable_override(struct pci_dev *pdev)
{

	if (dmi_check_system(cable_dmi_table))
		return 1;

	if (pdev->subsystem_vendor == 0x161F && pdev->subsystem_device == 0x2032)
		return 1;
	return 0;
}

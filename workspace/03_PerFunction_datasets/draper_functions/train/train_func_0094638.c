pci_get_hp_params(struct pci_dev *dev, struct hotplug_params *hpp)
{
	acpi_status status;
	acpi_handle handle, phandle;
	struct pci_bus *pbus;

	if (acpi_pci_disabled)
		return -ENODEV;

	handle = NULL;
	for (pbus = dev->bus; pbus; pbus = pbus->parent) {
		handle = acpi_pci_get_bridge_handle(pbus);
		if (handle)
			break;
	}


	while (handle) {
		status = acpi_run_hpx(handle, hpp);
		if (ACPI_SUCCESS(status))
			return 0;
		status = acpi_run_hpp(handle, hpp);
		if (ACPI_SUCCESS(status))
			return 0;
		if (acpi_is_root_bridge(handle))
			break;
		status = acpi_get_parent(handle, &phandle);
		if (ACPI_FAILURE(status))
			break;
		handle = phandle;
	}
	return -ENODEV;
}

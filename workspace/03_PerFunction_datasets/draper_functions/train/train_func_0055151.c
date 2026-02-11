amdgpu_atpx_detect(void)
{
	char acpi_method_name[255] = { 0 };
	struct acpi_buffer buffer = {sizeof(acpi_method_name), acpi_method_name};
	struct pci_dev *pdev = NULL;
	bool has_atpx = false;
	int vga_count = 0;

	while ((pdev = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, pdev)) != NULL) {
		vga_count++;

		has_atpx |= (amdgpu_atpx_pci_probe_handle(pdev) == true);
	}

	while ((pdev = pci_get_class(PCI_CLASS_DISPLAY_OTHER << 8, pdev)) != NULL) {
		vga_count++;

		has_atpx |= (amdgpu_atpx_pci_probe_handle(pdev) == true);
	}

	if (has_atpx && vga_count == 2) {
		acpi_get_name(amdgpu_atpx_priv.atpx.handle, ACPI_FULL_PATHNAME, &buffer);
		printk(KERN_INFO "vga_switcheroo: detected switching method %s handle\n",
		       acpi_method_name);
		amdgpu_atpx_priv.atpx_detected = true;
		return true;
	}
	return false;
}

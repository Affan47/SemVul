skd_pci_suspend(struct pci_dev *pdev, pm_message_t state)
{
	int i;
	struct skd_device *skdev;

	skdev = pci_get_drvdata(pdev);
	if (!skdev) {
		pr_err("%s: no device data for PCI\n", pci_name(pdev));
		return -EIO;
	}

	skd_stop_device(skdev);

	skd_release_irq(skdev);

	for (i = 0; i < SKD_MAX_BARS; i++)
		if (skdev->mem_map[i])
			iounmap((u32 *)skdev->mem_map[i]);

	if (skdev->pcie_error_reporting_is_enabled)
		pci_disable_pcie_error_reporting(pdev);

	pci_release_regions(pdev);
	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_set_power_state(pdev, pci_choose_state(pdev, state));
	return 0;
}

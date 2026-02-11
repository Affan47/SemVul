netxen_nic_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct netxen_adapter *adapter = pci_get_drvdata(pdev);
	int retval;

	netxen_nic_detach_func(adapter);

	retval = pci_save_state(pdev);
	if (retval)
		return retval;

	if (netxen_nic_wol_supported(adapter)) {
		pci_enable_wake(pdev, PCI_D3cold, 1);
		pci_enable_wake(pdev, PCI_D3hot, 1);
	}

	pci_disable_device(pdev);
	pci_set_power_state(pdev, pci_choose_state(pdev, state));

	return 0;
}

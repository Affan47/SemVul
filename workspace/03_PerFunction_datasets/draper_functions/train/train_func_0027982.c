qlcnic_83xx_io_slot_reset(struct pci_dev *pdev)
{
	struct qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	int err = 0;

	pdev->error_state = pci_channel_io_normal;
	err = pci_enable_device(pdev);
	if (err)
		goto disconnect;

	pci_set_power_state(pdev, PCI_D0);
	pci_set_master(pdev);
	pci_restore_state(pdev);

	err = qlcnic_83xx_aer_reset(adapter);
	if (err == 0)
		return PCI_ERS_RESULT_RECOVERED;
disconnect:
	clear_bit(__QLCNIC_AER, &adapter->state);
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	return PCI_ERS_RESULT_DISCONNECT;
}

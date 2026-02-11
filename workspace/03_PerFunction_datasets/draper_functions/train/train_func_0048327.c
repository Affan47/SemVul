be_eeh_reset(struct pci_dev *pdev)
{
	struct be_adapter *adapter = pci_get_drvdata(pdev);
	int status;

	dev_info(&adapter->pdev->dev, "EEH reset\n");

	status = pci_enable_device(pdev);
	if (status)
		return PCI_ERS_RESULT_DISCONNECT;

	pci_set_master(pdev);
	pci_restore_state(pdev);


	dev_info(&adapter->pdev->dev,
		 "Waiting for FW to be ready after EEH reset\n");
	status = be_fw_wait_ready(adapter);
	if (status)
		return PCI_ERS_RESULT_DISCONNECT;

	pci_cleanup_aer_uncorrect_error_status(pdev);
	be_clear_error(adapter, BE_CLEAR_ALL);
	return PCI_ERS_RESULT_RECOVERED;
}

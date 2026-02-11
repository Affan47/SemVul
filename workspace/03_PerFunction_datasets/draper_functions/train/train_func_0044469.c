beiscsi_eeh_reset(struct pci_dev *pdev)
{
	struct beiscsi_hba *phba = NULL;
	int status = 0;

	phba = (struct beiscsi_hba *)pci_get_drvdata(pdev);

	beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
		    "BM_%d : EEH Reset\n");

	status = pci_enable_device(pdev);
	if (status)
		return PCI_ERS_RESULT_DISCONNECT;

	pci_set_master(pdev);
	pci_set_power_state(pdev, PCI_D0);
	pci_restore_state(pdev);


	status = be_chk_reset_complete(phba);
	if (!status) {
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_INIT,
			    "BM_%d : EEH Reset Completed\n");
	} else {
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_INIT,
			    "BM_%d : EEH Reset Completion Failure\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}

	pci_cleanup_aer_uncorrect_error_status(pdev);
	return PCI_ERS_RESULT_RECOVERED;
}

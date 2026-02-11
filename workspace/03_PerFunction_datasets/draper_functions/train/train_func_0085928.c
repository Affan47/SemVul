ipr_pci_error_detected(struct pci_dev *pdev,
					       pci_channel_state_t state)
{
	switch (state) {
	case pci_channel_io_frozen:
		ipr_pci_frozen(pdev);
		return PCI_ERS_RESULT_CAN_RECOVER;
	case pci_channel_io_perm_failure:
		ipr_pci_perm_failure(pdev);
		return PCI_ERS_RESULT_DISCONNECT;
		break;
	default:
		break;
	}
	return PCI_ERS_RESULT_NEED_RESET;
}

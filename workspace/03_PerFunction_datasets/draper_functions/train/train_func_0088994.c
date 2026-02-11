s2io_io_slot_reset(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct s2io_nic *sp = netdev_priv(netdev);

	if (pci_enable_device(pdev)) {
		pr_err("Cannot re-enable PCI device after reset.\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}

	pci_set_master(pdev);
	s2io_reset(sp);

	return PCI_ERS_RESULT_RECOVERED;
}

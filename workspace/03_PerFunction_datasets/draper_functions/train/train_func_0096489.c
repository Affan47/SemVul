alx_pci_error_detected(struct pci_dev *pdev,
					       pci_channel_state_t state)
{
	struct alx_priv *alx = pci_get_drvdata(pdev);
	struct net_device *netdev = alx->dev;
	pci_ers_result_t rc = PCI_ERS_RESULT_NEED_RESET;

	dev_info(&pdev->dev, "pci error detected\n");

	rtnl_lock();

	if (netif_running(netdev)) {
		netif_device_detach(netdev);
		alx_halt(alx);
	}

	if (state == pci_channel_io_perm_failure)
		rc = PCI_ERS_RESULT_DISCONNECT;
	else
		pci_disable_device(pdev);

	rtnl_unlock();

	return rc;
}

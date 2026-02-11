s2io_io_resume(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct s2io_nic *sp = netdev_priv(netdev);

	if (netif_running(netdev)) {
		if (s2io_card_up(sp)) {
			pr_err("Can't bring device back up after reset.\n");
			return;
		}

		if (s2io_set_mac_addr(netdev, netdev->dev_addr) == FAILURE) {
			s2io_card_down(sp);
			pr_err("Can't restore mac addr after reset.\n");
			return;
		}
	}

	netif_device_attach(netdev);
	netif_tx_wake_all_queues(netdev);
}

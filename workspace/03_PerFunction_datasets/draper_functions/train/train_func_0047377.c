vlsi_tx_timeout(struct net_device *ndev)
{
	vlsi_irda_dev_t *idev = netdev_priv(ndev);


	vlsi_reg_debug(ndev->base_addr, __func__);
	vlsi_ring_debug(idev->tx_ring);

	if (netif_running(ndev))
		netif_stop_queue(ndev);

	vlsi_stop_hw(idev);


	if (!idev->new_baud)
		idev->new_baud = idev->baud;

	if (vlsi_start_hw(idev))
		net_err_ratelimited("%s: failed to restart hw - %s(%s) unusable!\n",
				    __func__, pci_name(idev->pdev), ndev->name);
	else
		netif_start_queue(ndev);
}

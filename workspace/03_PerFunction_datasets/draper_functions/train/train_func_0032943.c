igbvf_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct igbvf_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;


	set_bit(__IGBVF_DOWN, &adapter->state);
	del_timer_sync(&adapter->watchdog_timer);

	cancel_work_sync(&adapter->reset_task);
	cancel_work_sync(&adapter->watchdog_task);

	unregister_netdev(netdev);

	igbvf_reset_interrupt_capability(adapter);


	netif_napi_del(&adapter->rx_ring->napi);
	kfree(adapter->tx_ring);
	kfree(adapter->rx_ring);

	iounmap(hw->hw_addr);
	if (hw->flash_address)
		iounmap(hw->flash_address);
	pci_release_regions(pdev);

	free_netdev(netdev);

	pci_disable_device(pdev);
}

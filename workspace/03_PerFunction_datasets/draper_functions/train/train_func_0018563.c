i40evf_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct i40evf_adapter *adapter = netdev_priv(netdev);
	int retval = 0;

	netif_device_detach(netdev);

	if (netif_running(netdev)) {
		rtnl_lock();
		i40evf_down(adapter);
		rtnl_unlock();
	}
	i40evf_free_misc_irq(adapter);
	i40evf_reset_interrupt_capability(adapter);

	retval = pci_save_state(pdev);
	if (retval)
		return retval;

	pci_disable_device(pdev);

	return 0;
}

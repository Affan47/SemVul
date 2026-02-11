amd8111e_suspend(struct pci_dev *pci_dev, pm_message_t state)
{
	struct net_device *dev = pci_get_drvdata(pci_dev);
	struct amd8111e_priv *lp = netdev_priv(dev);

	if (!netif_running(dev))
		return 0;


	spin_lock_irq(&lp->lock);
	amd8111e_disable_interrupt(lp);
	spin_unlock_irq(&lp->lock);

	netif_device_detach(dev);


	spin_lock_irq(&lp->lock);
	if(lp->options & OPTION_DYN_IPG_ENABLE)
		del_timer_sync(&lp->ipg_data.ipg_timer);
	amd8111e_stop_chip(lp);
	spin_unlock_irq(&lp->lock);

	if(lp->options & OPTION_WOL_ENABLE){

		if(lp->options & OPTION_WAKE_MAGIC_ENABLE)
			amd8111e_enable_magicpkt(lp);
		if(lp->options & OPTION_WAKE_PHY_ENABLE)
			amd8111e_enable_link_change(lp);

		pci_enable_wake(pci_dev, PCI_D3hot, 1);
		pci_enable_wake(pci_dev, PCI_D3cold, 1);

	}
	else{
		pci_enable_wake(pci_dev, PCI_D3hot, 0);
		pci_enable_wake(pci_dev, PCI_D3cold, 0);
	}

	pci_save_state(pci_dev);
	pci_set_power_state(pci_dev, PCI_D3hot);

	return 0;
}

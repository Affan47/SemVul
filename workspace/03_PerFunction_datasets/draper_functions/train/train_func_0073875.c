de_suspend (struct pci_dev *pdev, pm_message_t state)
{
	struct net_device *dev = pci_get_drvdata (pdev);
	struct de_private *de = netdev_priv(dev);

	rtnl_lock();
	if (netif_running (dev)) {
		const int irq = pdev->irq;

		del_timer_sync(&de->media_timer);

		disable_irq(irq);
		spin_lock_irq(&de->lock);

		de_stop_hw(de);
		netif_stop_queue(dev);
		netif_device_detach(dev);
		netif_carrier_off(dev);

		spin_unlock_irq(&de->lock);
		enable_irq(irq);


		__de_get_stats(de);

		synchronize_irq(irq);
		de_clean_rings(de);

		de_adapter_sleep(de);
		pci_disable_device(pdev);
	} else {
		netif_device_detach(dev);
	}
	rtnl_unlock();
	return 0;
}

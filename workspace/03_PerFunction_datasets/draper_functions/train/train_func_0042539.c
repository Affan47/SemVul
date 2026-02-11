natsemi_suspend (struct pci_dev *pdev, pm_message_t state)
{
	struct net_device *dev = pci_get_drvdata (pdev);
	struct netdev_private *np = netdev_priv(dev);
	void __iomem * ioaddr = ns_ioaddr(dev);

	rtnl_lock();
	if (netif_running (dev)) {
		const int irq = np->pci_dev->irq;

		del_timer_sync(&np->timer);

		disable_irq(irq);
		spin_lock_irq(&np->lock);

		natsemi_irq_disable(dev);
		np->hands_off = 1;
		natsemi_stop_rxtx(dev);
		netif_stop_queue(dev);

		spin_unlock_irq(&np->lock);
		enable_irq(irq);

		napi_disable(&np->napi);


		__get_stats(dev);


		drain_ring(dev);
		{
			u32 wol = readl(ioaddr + WOLCmd) & WakeOptsSummary;

			if (wol) {


				enable_wol_mode(dev, 0);
			} else {

				writel(np->SavedClkRun, ioaddr + ClkRun);
			}
		}
	}
	netif_device_detach(dev);
	rtnl_unlock();
	return 0;
}

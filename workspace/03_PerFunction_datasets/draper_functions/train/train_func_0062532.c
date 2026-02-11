de_resume (struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata (pdev);
	struct de_private *de = netdev_priv(dev);
	int retval = 0;

	rtnl_lock();
	if (netif_device_present(dev))
		goto out;
	if (!netif_running(dev))
		goto out_attach;
	if ((retval = pci_enable_device(pdev))) {
		netdev_err(dev, "pci_enable_device failed in resume\n");
		goto out;
	}
	pci_set_master(pdev);
	de_init_rings(de);
	de_init_hw(de);
out_attach:
	netif_device_attach(dev);
out:
	rtnl_unlock();
	return 0;
}

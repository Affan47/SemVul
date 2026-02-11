prism2_pci_remove(struct pci_dev *pdev)
{
	struct net_device *dev;
	struct hostap_interface *iface;
	void __iomem *mem_start;
	struct hostap_pci_priv *hw_priv;

	dev = pci_get_drvdata(pdev);
	iface = netdev_priv(dev);
	hw_priv = iface->local->hw_priv;


	prism2_pci_cor_sreset(iface->local);
	hfa384x_disable_interrupts(dev);

	if (dev->irq)
		free_irq(dev->irq, dev);

	mem_start = hw_priv->mem_start;
	prism2_free_local_data(dev);
	kfree(hw_priv);

	iounmap(mem_start);

	release_mem_region(pci_resource_start(pdev, 0),
			   pci_resource_len(pdev, 0));
	pci_disable_device(pdev);
}

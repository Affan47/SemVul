skge_remove(struct pci_device *pdev)
{
	struct skge_hw *hw  = pci_get_drvdata(pdev);
	struct net_device *dev0, *dev1;

	if (!hw)
		return;

	if ((dev1 = hw->dev[1]))
		unregister_netdev(dev1);
	dev0 = hw->dev[0];
	unregister_netdev(dev0);

	hw->intr_mask = 0;
	skge_write32(hw, B0_IMSK, 0);
	skge_read32(hw, B0_IMSK);

	skge_write16(hw, B0_LED, LED_STAT_OFF);
	skge_write8(hw, B0_CTST, CS_RST_SET);

	if (dev1) {
		netdev_nullify(dev1);
		netdev_put(dev1);
	}
	netdev_nullify(dev0);
	netdev_put(dev0);

	iounmap((void*)hw->regs);
	free(hw);
	pci_set_drvdata(pdev, NULL);
}

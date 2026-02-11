alx_resume(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct alx_priv *alx = pci_get_drvdata(pdev);
	struct alx_hw *hw = &alx->hw;

	alx_reset_phy(hw);

	if (!netif_running(alx->dev))
		return 0;
	netif_device_attach(alx->dev);
	return __alx_open(alx, true);
}

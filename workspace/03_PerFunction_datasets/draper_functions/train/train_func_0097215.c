alx_free_irq(struct alx_priv *alx)
{
	struct pci_dev *pdev = alx->hw.pdev;

	free_irq(pdev->irq, alx);

	if (alx->msi) {
		pci_disable_msi(alx->hw.pdev);
		alx->msi = false;
	}
}

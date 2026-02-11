rtl_disable_msi(struct pci_dev *pdev, struct rtl8169_private *tp)
{
	if (tp->features & RTL_FEATURE_MSI) {
		pci_disable_msi(pdev);
		tp->features &= ~RTL_FEATURE_MSI;
	}
}

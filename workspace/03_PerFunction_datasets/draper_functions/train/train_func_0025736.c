rtl_pci_intr_mode_msi(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(pcipriv);
	int ret;

	ret = pci_enable_msi(rtlpci->pdev);
	if (ret < 0)
		return ret;

	ret = request_irq(rtlpci->pdev->irq, &_rtl_pci_interrupt,
			  IRQF_SHARED, KBUILD_MODNAME, hw);
	if (ret < 0) {
		pci_disable_msi(rtlpci->pdev);
		return ret;
	}

	rtlpci->using_msi = true;

	RT_TRACE(rtlpriv, COMP_INIT|COMP_INTR, DBG_DMESG,
		 "MSI Interrupt Mode!\n");
	return 0;
}

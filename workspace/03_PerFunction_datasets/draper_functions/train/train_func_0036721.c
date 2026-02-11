_rtl_pci_init_struct(struct ieee80211_hw *hw,
		struct pci_dev *pdev)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	rtlpci->up_first_time = true;
	rtlpci->being_init_adapter = false;

	rtlhal->hw = hw;
	rtlpci->pdev = pdev;


	_rtl_pci_init_trx_var(hw);

	 mac->beacon_interval = 100;


	mac->min_space_cfg = 0;
	mac->max_mss_density = 0;

	mac->current_ampdu_density = 7;
	mac->current_ampdu_factor = 3;


	rtlpci->acm_method = EACMWAY2_SW;


	tasklet_init(&rtlpriv->works.irq_tasklet,
		     (void (*)(unsigned long))_rtl_pci_irq_tasklet,
		     (unsigned long)hw);
	tasklet_init(&rtlpriv->works.irq_prepare_bcn_tasklet,
		     (void (*)(unsigned long))_rtl_pci_prepare_bcn_tasklet,
		     (unsigned long)hw);
	INIT_WORK(&rtlpriv->works.lps_change_work,
		  rtl_lps_change_work_callback);
}

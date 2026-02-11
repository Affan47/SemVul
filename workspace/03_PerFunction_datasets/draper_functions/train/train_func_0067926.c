rtl92se_disable_interrupt(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv;
	struct rtl_pci *rtlpci;

	rtlpriv = rtl_priv(hw);

	if (!rtlpriv || !rtlpriv->max_fw_size)
		return;
	rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	rtl_write_dword(rtlpriv, INTA_MASK, 0);
	rtl_write_dword(rtlpriv, INTA_MASK + 4, 0);
	rtlpci->irq_enabled = false;
}

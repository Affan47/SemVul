wlc_phy_classifier_nphy(struct brcms_phy *pi, u16 mask, u16 val)
{
	u16 curr_ctl, new_ctl;
	bool suspended = false;

	if (D11REV_IS(pi->sh->corerev, 16)) {
		suspended = (bcma_read32(pi->d11core, D11REGOFFS(maccontrol)) &
			     MCTL_EN_MAC) ? false : true;
		if (!suspended)
			wlapi_suspend_mac_and_wait(pi->sh->physhim);
	}

	curr_ctl = read_phy_reg(pi, 0xb0) & (0x7 << 0);

	new_ctl = (curr_ctl & (~mask)) | (val & mask);

	mod_phy_reg(pi, 0xb0, (0x7 << 0), new_ctl);

	if (D11REV_IS(pi->sh->corerev, 16) && !suspended)
		wlapi_enable_mac(pi->sh->physhim);

	return new_ctl;
}

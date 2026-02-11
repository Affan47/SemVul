brcms_c_suspend_mac_and_wait(struct brcms_c_info *wlc)
{
	struct brcms_hardware *wlc_hw = wlc->hw;
	struct bcma_device *core = wlc_hw->d11core;
	u32 mc, mi;

	brcms_dbg_mac80211(core, "wl%d: bandunit %d\n", wlc_hw->unit,
			   wlc_hw->band->bandunit);


	wlc_hw->mac_suspend_depth++;
	if (wlc_hw->mac_suspend_depth > 1)
		return;


	brcms_c_ucode_wake_override_set(wlc_hw, BRCMS_WAKE_OVERRIDE_MACSUSPEND);

	mc = bcma_read32(core, D11REGOFFS(maccontrol));

	if (mc == 0xffffffff) {
		brcms_err(core, "wl%d: %s: dead chip\n", wlc_hw->unit,
			  __func__);
		brcms_down(wlc->wl);
		return;
	}
	WARN_ON(mc & MCTL_PSM_JMP_0);
	WARN_ON(!(mc & MCTL_PSM_RUN));
	WARN_ON(!(mc & MCTL_EN_MAC));

	mi = bcma_read32(core, D11REGOFFS(macintstatus));
	if (mi == 0xffffffff) {
		brcms_err(core, "wl%d: %s: dead chip\n", wlc_hw->unit,
			  __func__);
		brcms_down(wlc->wl);
		return;
	}
	WARN_ON(mi & MI_MACSSPNDD);

	brcms_b_mctrl(wlc_hw, MCTL_EN_MAC, 0);

	SPINWAIT(!(bcma_read32(core, D11REGOFFS(macintstatus)) & MI_MACSSPNDD),
		 BRCMS_MAX_MAC_SUSPEND);

	if (!(bcma_read32(core, D11REGOFFS(macintstatus)) & MI_MACSSPNDD)) {
		brcms_err(core, "wl%d: wlc_suspend_mac_and_wait: waited %d uS"
			  " and MI_MACSSPNDD is still not on.\n",
			  wlc_hw->unit, BRCMS_MAX_MAC_SUSPEND);
		brcms_err(core, "wl%d: psmdebug 0x%08x, phydebug 0x%08x, "
			  "psm_brc 0x%04x\n", wlc_hw->unit,
			  bcma_read32(core, D11REGOFFS(psmdebug)),
			  bcma_read32(core, D11REGOFFS(phydebug)),
			  bcma_read16(core, D11REGOFFS(psm_brc)));
	}

	mc = bcma_read32(core, D11REGOFFS(maccontrol));
	if (mc == 0xffffffff) {
		brcms_err(core, "wl%d: %s: dead chip\n", wlc_hw->unit,
			  __func__);
		brcms_down(wlc->wl);
		return;
	}
	WARN_ON(mc & MCTL_PSM_JMP_0);
	WARN_ON(!(mc & MCTL_PSM_RUN));
	WARN_ON(mc & MCTL_EN_MAC);
}

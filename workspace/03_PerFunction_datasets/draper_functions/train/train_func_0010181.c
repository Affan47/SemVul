brcms_b_core_phy_clk(struct brcms_hardware *wlc_hw, bool clk)
{
	brcms_dbg_info(wlc_hw->d11core, "wl%d: clk %d\n", wlc_hw->unit, clk);

	wlc_hw->phyclk = clk;

	if (OFF == clk) {

		brcms_b_core_ioctl(wlc_hw, (SICF_PRST | SICF_FGC | SICF_GMODE),
				   (SICF_PRST | SICF_FGC));
		udelay(1);
		brcms_b_core_ioctl(wlc_hw, (SICF_PRST | SICF_FGC), SICF_PRST);
		udelay(1);

	} else {

		brcms_b_core_ioctl(wlc_hw, (SICF_PRST | SICF_FGC), SICF_FGC);
		udelay(1);
		brcms_b_core_ioctl(wlc_hw, SICF_FGC, 0);
		udelay(1);

	}
}

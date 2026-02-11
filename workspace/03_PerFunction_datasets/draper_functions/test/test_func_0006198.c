brcms_b_macphyclk_set(struct brcms_hardware *wlc_hw, bool clk)
{
	if (ON == clk)
		brcms_b_core_ioctl(wlc_hw, SICF_MPCLKE, SICF_MPCLKE);
	else
		brcms_b_core_ioctl(wlc_hw, SICF_MPCLKE, 0);
}

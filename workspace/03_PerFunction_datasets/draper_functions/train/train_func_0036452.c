fm10k_ptp_adjfreq(struct ptp_clock_info *ptp, s32 ppb)
{
	struct fm10k_intfc *interface;
	struct fm10k_hw *hw;
	int err;

	interface = container_of(ptp, struct fm10k_intfc, ptp_caps);
	hw = &interface->hw;

	err = hw->mac.ops.adjust_systime(hw, ppb);


	return (err == FM10K_ERR_PARAM) ? -ERANGE : err;
}

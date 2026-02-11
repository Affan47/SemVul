fm_config_rx_mute_reg(struct fmdev *fmdev)
{
	u16 payload, muteval;
	int ret;

	muteval = 0;
	switch (fmdev->rx.mute_mode) {
	case FM_MUTE_ON:
		muteval = FM_RX_AC_MUTE_MODE;
		break;

	case FM_MUTE_OFF:
		muteval = FM_RX_UNMUTE_MODE;
		break;

	case FM_MUTE_ATTENUATE:
		muteval = FM_RX_SOFT_MUTE_FORCE_MODE;
		break;
	}
	if (fmdev->rx.rf_depend_mute == FM_RX_RF_DEPENDENT_MUTE_ON)
		muteval |= FM_RX_RF_DEP_MODE;
	else
		muteval &= ~FM_RX_RF_DEP_MODE;

	payload = muteval;
	ret = fmc_send_cmd(fmdev, MUTE_STATUS_SET, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	return 0;
}

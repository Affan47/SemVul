ath9k_htc_beacon_config_sta(struct ath9k_htc_priv *priv,
					struct ath_beacon_config *bss_conf)
{
	struct ath9k_beacon_state bs;
	enum ath9k_int imask = 0;
	__be32 htc_imask = 0;
	int ret __attribute__ ((unused));
	u8 cmd_rsp;

	if (ath9k_cmn_beacon_config_sta(priv->ah, bss_conf, &bs) == -EPERM)
		return;

	WMI_CMD(WMI_DISABLE_INTR_CMDID);
	ath9k_hw_set_sta_beacon_timers(priv->ah, &bs);
	imask |= ATH9K_INT_BMISS;
	htc_imask = cpu_to_be32(imask);
	WMI_CMD_BUF(WMI_ENABLE_INTR_CMDID, &htc_imask);
}

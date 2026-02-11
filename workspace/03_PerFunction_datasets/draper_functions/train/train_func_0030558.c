ath9k_htc_start(struct ieee80211_hw *hw)
{
	struct ath9k_htc_priv *priv = hw->priv;
	struct ath_hw *ah = priv->ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ieee80211_channel *curchan = hw->conf.chandef.chan;
	struct ath9k_channel *init_channel;
	int ret = 0;
	enum htc_phymode mode;
	__be16 htc_mode;
	u8 cmd_rsp;

	mutex_lock(&priv->mutex);

	ath_dbg(common, CONFIG,
		"Starting driver with initial channel: %d MHz\n",
		curchan->center_freq);


	ath9k_htc_setpower(priv, ATH9K_PM_AWAKE);
	WMI_CMD(WMI_FLUSH_RECV_CMDID);


	init_channel = ath9k_cmn_get_channel(hw, ah, &hw->conf.chandef);

	ret = ath9k_hw_reset(ah, init_channel, ah->caldata, false);
	if (ret) {
		ath_err(common,
			"Unable to reset hardware; reset status %d (freq %u MHz)\n",
			ret, curchan->center_freq);
		mutex_unlock(&priv->mutex);
		return ret;
	}

	ath9k_cmn_update_txpow(ah, priv->curtxpow, priv->txpowlimit,
			       &priv->curtxpow);

	mode = ath9k_htc_get_curmode(priv, init_channel);
	htc_mode = cpu_to_be16(mode);
	WMI_CMD_BUF(WMI_SET_MODE_CMDID, &htc_mode);
	WMI_CMD(WMI_ATH_INIT_CMDID);
	WMI_CMD(WMI_START_RECV_CMDID);

	ath9k_host_rx_init(priv);

	ret = ath9k_htc_update_cap_target(priv, 0);
	if (ret)
		ath_dbg(common, CONFIG,
			"Failed to update capability in target\n");

	clear_bit(ATH_OP_INVALID, &common->op_flags);
	htc_start(priv->htc);

	spin_lock_bh(&priv->tx.tx_lock);
	priv->tx.flags &= ~ATH9K_HTC_OP_TX_QUEUES_STOP;
	spin_unlock_bh(&priv->tx.tx_lock);

	ieee80211_wake_queues(hw);

	mod_timer(&priv->tx.cleanup_timer,
		  jiffies + msecs_to_jiffies(ATH9K_HTC_TX_CLEANUP_INTERVAL));

	ath9k_htc_start_btcoex(priv);

	mutex_unlock(&priv->mutex);

	return ret;
}

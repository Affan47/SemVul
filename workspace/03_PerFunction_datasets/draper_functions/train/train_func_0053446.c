ath6kl_cfg80211_set_txe_config(struct wiphy *wiphy,
					  struct net_device *dev,
					  u32 rate, u32 pkts, u32 intvl)
{
	struct ath6kl *ar = ath6kl_priv(dev);
	struct ath6kl_vif *vif = netdev_priv(dev);

	if (vif->nw_type != INFRA_NETWORK ||
	    !test_bit(ATH6KL_FW_CAPABILITY_TX_ERR_NOTIFY, ar->fw_capabilities))
		return -EOPNOTSUPP;

	if (vif->sme_state != SME_CONNECTED)
		return -ENOTCONN;


	vif->txe_intvl = intvl;

	return ath6kl_wmi_set_txe_notify(ar->wmi, vif->fw_vif_idx,
					 rate, pkts, intvl);
}

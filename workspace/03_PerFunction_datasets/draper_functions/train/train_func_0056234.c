ath6kl_flush_pmksa(struct wiphy *wiphy, struct net_device *netdev)
{
	struct ath6kl *ar = ath6kl_priv(netdev);
	struct ath6kl_vif *vif = netdev_priv(netdev);

	if (test_bit(CONNECTED, &vif->flags))
		return ath6kl_wmi_setpmkid_cmd(ar->wmi, vif->fw_vif_idx,
					       vif->bssid, NULL, false);
	return 0;
}

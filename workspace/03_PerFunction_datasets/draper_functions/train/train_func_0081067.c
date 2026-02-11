ath10k_mac_setup_prb_tmpl(struct ath10k_vif *arvif)
{
	struct ath10k *ar = arvif->ar;
	struct ieee80211_hw *hw = ar->hw;
	struct ieee80211_vif *vif = arvif->vif;
	struct sk_buff *prb;
	int ret;

	if (!test_bit(WMI_SERVICE_BEACON_OFFLOAD, ar->wmi.svc_map))
		return 0;

	if (arvif->vdev_type != WMI_VDEV_TYPE_AP)
		return 0;

	prb = ieee80211_proberesp_get(hw, vif);
	if (!prb) {
		ath10k_warn(ar, "failed to get probe resp template from mac80211\n");
		return -EPERM;
	}

	ret = ath10k_wmi_prb_tmpl(ar, arvif->vdev_id, prb);
	kfree_skb(prb);

	if (ret) {
		ath10k_warn(ar, "failed to submit probe resp template command: %d\n",
			    ret);
		return ret;
	}

	return 0;
}

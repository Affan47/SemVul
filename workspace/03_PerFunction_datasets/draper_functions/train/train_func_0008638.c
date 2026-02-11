carl9170_update_beacon(struct ar9170 *ar, const bool submit)
{
	struct sk_buff *skb = NULL;
	struct carl9170_vif_info *cvif;
	__le32 *data, *old = NULL;
	u32 word, ht1, plcp, off, addr, len;
	int i = 0, err = 0;
	bool ht_rate;

	rcu_read_lock();
	cvif = carl9170_pick_beaconing_vif(ar);
	if (!cvif)
		goto out_unlock;

	skb = ieee80211_beacon_get_tim(ar->hw, carl9170_get_vif(cvif),
		NULL, NULL);

	if (!skb) {
		err = -ENOMEM;
		goto err_free;
	}

	spin_lock_bh(&ar->beacon_lock);
	data = (__le32 *)skb->data;
	if (cvif->beacon)
		old = (__le32 *)cvif->beacon->data;

	off = cvif->id * AR9170_MAC_BCN_LENGTH_MAX;
	addr = ar->fw.beacon_addr + off;
	len = roundup(skb->len + FCS_LEN, 4);

	if ((off + len) > ar->fw.beacon_max_len) {
		if (net_ratelimit()) {
			wiphy_err(ar->hw->wiphy, "beacon does not "
				  "fit into device memory!\n");
		}
		err = -EINVAL;
		goto err_unlock;
	}

	if (len > AR9170_MAC_BCN_LENGTH_MAX) {
		if (net_ratelimit()) {
			wiphy_err(ar->hw->wiphy, "no support for beacons "
				"bigger than %d (yours:%d).\n",
				 AR9170_MAC_BCN_LENGTH_MAX, len);
		}

		err = -EMSGSIZE;
		goto err_unlock;
	}

	ht_rate = carl9170_tx_beacon_physet(ar, skb, &ht1, &plcp);

	carl9170_async_regwrite_begin(ar);
	carl9170_async_regwrite(AR9170_MAC_REG_BCN_HT1, ht1);
	if (ht_rate)
		carl9170_async_regwrite(AR9170_MAC_REG_BCN_HT2, plcp);
	else
		carl9170_async_regwrite(AR9170_MAC_REG_BCN_PLCP, plcp);

	for (i = 0; i < DIV_ROUND_UP(skb->len, 4); i++) {


		if (old && (data[i] == old[i]))
			continue;

		word = le32_to_cpu(data[i]);
		carl9170_async_regwrite(addr + 4 * i, word);
	}
	carl9170_async_regwrite_finish();

	dev_kfree_skb_any(cvif->beacon);
	cvif->beacon = NULL;

	err = carl9170_async_regwrite_result();
	if (!err)
		cvif->beacon = skb;
	spin_unlock_bh(&ar->beacon_lock);
	if (err)
		goto err_free;

	if (submit) {
		err = carl9170_bcn_ctrl(ar, cvif->id,
					CARL9170_BCN_CTRL_CAB_TRIGGER,
					addr, skb->len + FCS_LEN);

		if (err)
			goto err_free;
	}
out_unlock:
	rcu_read_unlock();
	return 0;

err_unlock:
	spin_unlock_bh(&ar->beacon_lock);

err_free:
	rcu_read_unlock();
	dev_kfree_skb_any(skb);
	return err;
}

carl9170_op_conf_tx(struct ieee80211_hw *hw,
			       struct ieee80211_vif *vif, u16 queue,
			       const struct ieee80211_tx_queue_params *param)
{
	struct ar9170 *ar = hw->priv;
	int ret;

	mutex_lock(&ar->mutex);
	if (queue < ar->hw->queues) {
		osb();
		memcpy(&ar->edcf[ar9170_qmap[queue]], param, sizeof(*param));
		ret = carl9170_set_qos(ar);
	} else {
		ret = -EINVAL;
	}

	mutex_unlock(&ar->mutex);
	return ret;
}

carl9170_op_flush(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif,
			      u32 queues, bool drop)
{
	struct ar9170 *ar = hw->priv;
	unsigned int vid;

	mutex_lock(&ar->mutex);
	for_each_set_bit(vid, &ar->vif_bitmap, ar->fw.vif_num)
		carl9170_flush_cab(ar, vid);

	carl9170_flush(ar, drop);
	mutex_unlock(&ar->mutex);
}

ath10k_htt_rx_h_peer_channel(struct ath10k *ar, struct htt_rx_desc *rxd)
{
	struct ath10k_peer *peer;
	struct ath10k_vif *arvif;
	struct cfg80211_chan_def def;
	u16 peer_id;

	lockdep_assert_held(&ar->data_lock);

	if (!rxd)
		return NULL;

	if (rxd->attention.flags &
	    __cpu_to_le32(RX_ATTENTION_FLAGS_PEER_IDX_INVALID))
		return NULL;

	if (!(rxd->msdu_end.common.info0 &
	      __cpu_to_le32(RX_MSDU_END_INFO0_FIRST_MSDU)))
		return NULL;

	peer_id = MS(__le32_to_cpu(rxd->mpdu_start.info0),
		     RX_MPDU_START_INFO0_PEER_IDX);

	peer = ath10k_peer_find_by_id(ar, peer_id);
	if (!peer)
		return NULL;

	arvif = ath10k_get_arvif(ar, peer->vdev_id);
	if (WARN_ON_ONCE(!arvif))
		return NULL;

	if (WARN_ON(ath10k_mac_vif_chan(arvif->vif, &def)))
		return NULL;

	return def.chan;
}

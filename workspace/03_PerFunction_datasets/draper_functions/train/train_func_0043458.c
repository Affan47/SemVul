b43legacy_pio_handle_txstatus(struct b43legacy_wldev *dev,
				   const struct b43legacy_txstatus *status)
{
	struct b43legacy_pioqueue *queue;
	struct b43legacy_pio_txpacket *packet;
	struct ieee80211_tx_info *info;
	int retry_limit;

	queue = parse_cookie(dev, status->cookie, &packet);
	B43legacy_WARN_ON(!queue);

	if (!packet->skb)
		return;

	queue->tx_devq_packets--;
	queue->tx_devq_used -= (packet->skb->len +
				sizeof(struct b43legacy_txhdr_fw3));

	info = IEEE80211_SKB_CB(packet->skb);


	retry_limit = info->status.rates[0].count;
	ieee80211_tx_info_clear_status(info);

	if (status->acked)
		info->flags |= IEEE80211_TX_STAT_ACK;

	if (status->rts_count > dev->wl->hw->conf.short_frame_max_tx_count) {


		info->status.rates[0].count = 0;
		info->status.rates[1].count = status->frame_count;
	} else {
		if (status->frame_count > retry_limit) {
			info->status.rates[0].count = retry_limit;
			info->status.rates[1].count = status->frame_count -
					retry_limit;

		} else {
			info->status.rates[0].count = status->frame_count;
			info->status.rates[1].idx = -1;
		}
	}
	ieee80211_tx_status_irqsafe(dev->wl->hw, packet->skb);
	packet->skb = NULL;

	free_txpacket(packet, 1);


	if (!list_empty(&queue->txqueue))
		tasklet_schedule(&queue->txtask);
}

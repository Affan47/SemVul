ath10k_wmi_10_2_4_op_pull_fw_stats(struct ath10k *ar,
					      struct sk_buff *skb,
					      struct ath10k_fw_stats *stats)
{
	const struct wmi_10_2_stats_event *ev = (void *)skb->data;
	u32 num_pdev_stats;
	u32 num_pdev_ext_stats;
	u32 num_vdev_stats;
	u32 num_peer_stats;
	int i;

	if (!skb_pull(skb, sizeof(*ev)))
		return -EPROTO;

	num_pdev_stats = __le32_to_cpu(ev->num_pdev_stats);
	num_pdev_ext_stats = __le32_to_cpu(ev->num_pdev_ext_stats);
	num_vdev_stats = __le32_to_cpu(ev->num_vdev_stats);
	num_peer_stats = __le32_to_cpu(ev->num_peer_stats);

	for (i = 0; i < num_pdev_stats; i++) {
		const struct wmi_10_2_pdev_stats *src;
		struct ath10k_fw_stats_pdev *dst;

		src = (void *)skb->data;
		if (!skb_pull(skb, sizeof(*src)))
			return -EPROTO;

		dst = kzalloc(sizeof(*dst), GFP_ATOMIC);
		if (!dst)
			continue;

		ath10k_wmi_pull_pdev_stats_base(&src->base, dst);
		ath10k_wmi_pull_pdev_stats_tx(&src->tx, dst);
		ath10k_wmi_pull_pdev_stats_rx(&src->rx, dst);
		ath10k_wmi_pull_pdev_stats_extra(&src->extra, dst);


		list_add_tail(&dst->list, &stats->pdevs);
	}

	for (i = 0; i < num_pdev_ext_stats; i++) {
		const struct wmi_10_2_pdev_ext_stats *src;

		src = (void *)skb->data;
		if (!skb_pull(skb, sizeof(*src)))
			return -EPROTO;


	}


	for (i = 0; i < num_peer_stats; i++) {
		const struct wmi_10_2_4_peer_stats *src;
		struct ath10k_fw_stats_peer *dst;

		src = (void *)skb->data;
		if (!skb_pull(skb, sizeof(*src)))
			return -EPROTO;

		dst = kzalloc(sizeof(*dst), GFP_ATOMIC);
		if (!dst)
			continue;

		ath10k_wmi_pull_peer_stats(&src->common.old, dst);

		dst->peer_rx_rate = __le32_to_cpu(src->common.peer_rx_rate);


		list_add_tail(&dst->list, &stats->peers);
	}

	return 0;
}

fm10k_ts_tx_skb(struct fm10k_intfc *interface,
				       __le16 dglort)
{
	struct sk_buff_head *list = &interface->ts_tx_skb_queue;
	struct sk_buff *skb;

	skb_queue_walk(list, skb) {
		if (FM10K_CB(skb)->fi.w.dglort == dglort)
			return skb;
	}

	return NULL;
}

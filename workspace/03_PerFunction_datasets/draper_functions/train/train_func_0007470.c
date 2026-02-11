brcmf_fws_hanger_cleanup(struct brcmf_fws_info *fws,
				     bool (*fn)(struct sk_buff *, void *),
				     int ifidx)
{
	struct brcmf_fws_hanger *h = &fws->hanger;
	struct sk_buff *skb;
	int i;
	enum brcmf_fws_hanger_item_state s;

	for (i = 0; i < ARRAY_SIZE(h->items); i++) {
		s = h->items[i].state;
		if (s == BRCMF_FWS_HANGER_ITEM_STATE_INUSE ||
		    s == BRCMF_FWS_HANGER_ITEM_STATE_INUSE_SUPPRESSED) {
			skb = h->items[i].pkt;
			if (fn == NULL || fn(skb, &ifidx)) {

				if (s == BRCMF_FWS_HANGER_ITEM_STATE_INUSE)
					brcmu_pkt_buf_free_skb(skb);
				h->items[i].state =
					BRCMF_FWS_HANGER_ITEM_STATE_FREE;
			}
		}
	}
}

xenvif_fill_frags(struct xenvif_queue *queue, struct sk_buff *skb)
{
	struct skb_shared_info *shinfo = skb_shinfo(skb);
	int nr_frags = shinfo->nr_frags;
	int i;
	u16 prev_pending_idx = INVALID_PENDING_IDX;

	for (i = 0; i < nr_frags; i++) {
		skb_frag_t *frag = shinfo->frags + i;
		struct xen_netif_tx_request *txp;
		struct page *page;
		u16 pending_idx;

		pending_idx = frag_get_pending_idx(frag);


		if (prev_pending_idx == INVALID_PENDING_IDX)
			skb_shinfo(skb)->destructor_arg =
				&callback_param(queue, pending_idx);
		else
			callback_param(queue, prev_pending_idx).ctx =
				&callback_param(queue, pending_idx);

		callback_param(queue, pending_idx).ctx = NULL;
		prev_pending_idx = pending_idx;

		txp = &queue->pending_tx_info[pending_idx].req;
		page = virt_to_page(idx_to_kaddr(queue, pending_idx));
		__skb_fill_page_desc(skb, i, page, txp->offset, txp->size);
		skb->len += txp->size;
		skb->data_len += txp->size;
		skb->truesize += txp->size;


		get_page(queue->mmap_pages[pending_idx]);
	}
}

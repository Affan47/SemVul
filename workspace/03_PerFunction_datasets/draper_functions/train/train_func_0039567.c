bnad_rxq_alloc_init(struct bnad *bnad, struct bna_rcb *rcb)
{
	struct bnad_rx_unmap_q *unmap_q = rcb->unmap_q;
	int order;

	bnad_rxq_alloc_uninit(bnad, rcb);

	order = get_order(rcb->rxq->buffer_size);

	unmap_q->type = BNAD_RXBUF_PAGE;

	if (bna_is_small_rxq(rcb->id)) {
		unmap_q->alloc_order = 0;
		unmap_q->map_size = rcb->rxq->buffer_size;
	} else {
		if (rcb->rxq->multi_buffer) {
			unmap_q->alloc_order = 0;
			unmap_q->map_size = rcb->rxq->buffer_size;
			unmap_q->type = BNAD_RXBUF_MULTI_BUFF;
		} else {
			unmap_q->alloc_order = order;
			unmap_q->map_size =
				(rcb->rxq->buffer_size > 2048) ?
				PAGE_SIZE << order : 2048;
		}
	}

	BUG_ON((PAGE_SIZE << order) % unmap_q->map_size);

	return 0;
}

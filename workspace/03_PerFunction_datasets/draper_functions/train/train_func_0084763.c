refill_fl(struct adapter *adap, struct sge_fl *q, int n, gfp_t gfp)
{
	struct rx_sw_desc *sd = &q->sdesc[q->pidx];
	struct rx_desc *d = &q->desc[q->pidx];
	unsigned int count = 0;

	while (n--) {
		dma_addr_t mapping;
		int err;

		if (q->use_pages) {
			if (unlikely(alloc_pg_chunk(adap, q, sd, gfp,
						    q->order))) {
nomem:				q->alloc_failed++;
				break;
			}
			mapping = sd->pg_chunk.mapping + sd->pg_chunk.offset;
			dma_unmap_addr_set(sd, dma_addr, mapping);

			add_one_rx_chunk(mapping, d, q->gen);
			pci_dma_sync_single_for_device(adap->pdev, mapping,
						q->buf_size - SGE_PG_RSVD,
						PCI_DMA_FROMDEVICE);
		} else {
			void *buf_start;

			struct sk_buff *skb = alloc_skb(q->buf_size, gfp);
			if (!skb)
				goto nomem;

			sd->skb = skb;
			buf_start = skb->data;
			err = add_one_rx_buf(buf_start, q->buf_size, d, sd,
					     q->gen, adap->pdev);
			if (unlikely(err)) {
				clear_rx_desc(adap->pdev, q, sd);
				break;
			}
		}

		d++;
		sd++;
		if (++q->pidx == q->size) {
			q->pidx = 0;
			q->gen ^= 1;
			sd = q->sdesc;
			d = q->desc;
		}
		count++;
	}

	q->credits += count;
	q->pend_cred += count;
	ring_fl_db(adap, q);

	return count;
}

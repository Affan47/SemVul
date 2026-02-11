bnxt_tx_int(struct bnxt *bp, struct bnxt_napi *bnapi, int nr_pkts)
{
	struct bnxt_tx_ring_info *txr = &bnapi->tx_ring;
	int index = bnapi->index;
	struct netdev_queue *txq = netdev_get_tx_queue(bp->dev, index);
	u16 cons = txr->tx_cons;
	struct pci_dev *pdev = bp->pdev;
	int i;
	unsigned int tx_bytes = 0;

	for (i = 0; i < nr_pkts; i++) {
		struct bnxt_sw_tx_bd *tx_buf;
		struct sk_buff *skb;
		int j, last;

		tx_buf = &txr->tx_buf_ring[cons];
		cons = NEXT_TX(cons);
		skb = tx_buf->skb;
		tx_buf->skb = NULL;

		if (tx_buf->is_push) {
			tx_buf->is_push = 0;
			goto next_tx_int;
		}

		dma_unmap_single(&pdev->dev, dma_unmap_addr(tx_buf, mapping),
				 skb_headlen(skb), PCI_DMA_TODEVICE);
		last = tx_buf->nr_frags;

		for (j = 0; j < last; j++) {
			cons = NEXT_TX(cons);
			tx_buf = &txr->tx_buf_ring[cons];
			dma_unmap_page(
				&pdev->dev,
				dma_unmap_addr(tx_buf, mapping),
				skb_frag_size(&skb_shinfo(skb)->frags[j]),
				PCI_DMA_TODEVICE);
		}

next_tx_int:
		cons = NEXT_TX(cons);

		tx_bytes += skb->len;
		dev_kfree_skb_any(skb);
	}

	netdev_tx_completed_queue(txq, nr_pkts, tx_bytes);
	txr->tx_cons = cons;


	smp_mb();

	if (unlikely(netif_tx_queue_stopped(txq)) &&
	    (bnxt_tx_avail(bp, txr) > bp->tx_wake_thresh)) {
		__netif_tx_lock(txq, smp_processor_id());
		if (netif_tx_queue_stopped(txq) &&
		    bnxt_tx_avail(bp, txr) > bp->tx_wake_thresh &&
		    txr->dev_state != BNXT_DEV_STATE_CLOSING)
			netif_tx_wake_queue(txq);
		__netif_tx_unlock(txq);
	}
}

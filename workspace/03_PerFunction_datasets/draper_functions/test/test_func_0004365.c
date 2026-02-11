bnx2_free_tx_skbs(struct bnx2 *bp)
{
	int i;

	for (i = 0; i < bp->num_tx_rings; i++) {
		struct bnx2_napi *bnapi = &bp->bnx2_napi[i];
		struct bnx2_tx_ring_info *txr = &bnapi->tx_ring;
		int j;

		if (txr->tx_buf_ring == NULL)
			continue;

		for (j = 0; j < BNX2_TX_DESC_CNT; ) {
			struct bnx2_sw_tx_bd *tx_buf = &txr->tx_buf_ring[j];
			struct sk_buff *skb = tx_buf->skb;
			int k, last;

			if (skb == NULL) {
				j = BNX2_NEXT_TX_BD(j);
				continue;
			}

			dma_unmap_single(&bp->pdev->dev,
					 dma_unmap_addr(tx_buf, mapping),
					 skb_headlen(skb),
					 PCI_DMA_TODEVICE);

			tx_buf->skb = NULL;

			last = tx_buf->nr_frags;
			j = BNX2_NEXT_TX_BD(j);
			for (k = 0; k < last; k++, j = BNX2_NEXT_TX_BD(j)) {
				tx_buf = &txr->tx_buf_ring[BNX2_TX_RING_IDX(j)];
				dma_unmap_page(&bp->pdev->dev,
					dma_unmap_addr(tx_buf, mapping),
					skb_frag_size(&skb_shinfo(skb)->frags[k]),
					PCI_DMA_TODEVICE);
			}
			dev_kfree_skb(skb);
		}
		netdev_tx_reset_queue(netdev_get_tx_queue(bp->dev, i));
	}
}

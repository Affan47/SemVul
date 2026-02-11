macb_alloc_consistent(struct macb *bp)
{
	struct macb_queue *queue;
	unsigned int q;
	int size;

	for (q = 0, queue = bp->queues; q < bp->num_queues; ++q, ++queue) {
		size = TX_RING_BYTES;
		queue->tx_ring = dma_alloc_coherent(&bp->pdev->dev, size,
						    &queue->tx_ring_dma,
						    GFP_KERNEL);
		if (!queue->tx_ring)
			goto out_err;
		netdev_dbg(bp->dev,
			   "Allocated TX ring for queue %u of %d bytes at %08lx (mapped %p)\n",
			   q, size, (unsigned long)queue->tx_ring_dma,
			   queue->tx_ring);

		size = TX_RING_SIZE * sizeof(struct macb_tx_skb);
		queue->tx_skb = kmalloc(size, GFP_KERNEL);
		if (!queue->tx_skb)
			goto out_err;
	}

	size = RX_RING_BYTES;
	bp->rx_ring = dma_alloc_coherent(&bp->pdev->dev, size,
					 &bp->rx_ring_dma, GFP_KERNEL);
	if (!bp->rx_ring)
		goto out_err;
	netdev_dbg(bp->dev,
		   "Allocated RX ring of %d bytes at %08lx (mapped %p)\n",
		   size, (unsigned long)bp->rx_ring_dma, bp->rx_ring);

	if (bp->macbgem_ops.mog_alloc_rx_buffers(bp))
		goto out_err;

	return 0;

out_err:
	macb_free_consistent(bp);
	return -ENOMEM;
}

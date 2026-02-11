il4965_rx_queue_restock(struct il_priv *il)
{
	struct il_rx_queue *rxq = &il->rxq;
	struct list_head *element;
	struct il_rx_buf *rxb;
	unsigned long flags;

	spin_lock_irqsave(&rxq->lock, flags);
	while (il_rx_queue_space(rxq) > 0 && rxq->free_count) {

		rxb = rxq->queue[rxq->write];
		BUG_ON(rxb && rxb->page);


		element = rxq->rx_free.next;
		rxb = list_entry(element, struct il_rx_buf, list);
		list_del(element);


		rxq->bd[rxq->write] =
		    il4965_dma_addr2rbd_ptr(il, rxb->page_dma);
		rxq->queue[rxq->write] = rxb;
		rxq->write = (rxq->write + 1) & RX_QUEUE_MASK;
		rxq->free_count--;
	}
	spin_unlock_irqrestore(&rxq->lock, flags);


	if (rxq->free_count <= RX_LOW_WATERMARK)
		queue_work(il->workqueue, &il->rx_replenish);


	if (rxq->write_actual != (rxq->write & ~0x7)) {
		spin_lock_irqsave(&rxq->lock, flags);
		rxq->need_update = 1;
		spin_unlock_irqrestore(&rxq->lock, flags);
		il_rx_queue_update_write_ptr(il, rxq);
	}
}

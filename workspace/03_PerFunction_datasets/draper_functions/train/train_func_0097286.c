xenvif_tx_err(struct xenvif_queue *queue,
			  struct xen_netif_tx_request *txp, RING_IDX end)
{
	RING_IDX cons = queue->tx.req_cons;
	unsigned long flags;

	do {
		spin_lock_irqsave(&queue->response_lock, flags);
		make_tx_response(queue, txp, XEN_NETIF_RSP_ERROR);
		push_tx_responses(queue);
		spin_unlock_irqrestore(&queue->response_lock, flags);
		if (cons == end)
			break;
		RING_COPY_REQUEST(&queue->tx, cons++, txp);
	} while (1);
	queue->tx.req_cons = cons;
}

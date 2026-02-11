xenvif_read_io_ring(struct seq_file *m, void *v)
{
	struct xenvif_queue *queue = m->private;
	struct xen_netif_tx_back_ring *tx_ring = &queue->tx;
	struct xen_netif_rx_back_ring *rx_ring = &queue->rx;
	struct netdev_queue *dev_queue;

	if (tx_ring->sring) {
		struct xen_netif_tx_sring *sring = tx_ring->sring;

		seq_printf(m, "Queue %d\nTX: nr_ents %u\n", queue->id,
			   tx_ring->nr_ents);
		seq_printf(m, "req prod %u (%d) cons %u (%d) event %u (%d)\n",
			   sring->req_prod,
			   sring->req_prod - sring->rsp_prod,
			   tx_ring->req_cons,
			   tx_ring->req_cons - sring->rsp_prod,
			   sring->req_event,
			   sring->req_event - sring->rsp_prod);
		seq_printf(m, "rsp prod %u (base) pvt %u (%d) event %u (%d)\n",
			   sring->rsp_prod,
			   tx_ring->rsp_prod_pvt,
			   tx_ring->rsp_prod_pvt - sring->rsp_prod,
			   sring->rsp_event,
			   sring->rsp_event - sring->rsp_prod);
		seq_printf(m, "pending prod %u pending cons %u nr_pending_reqs %u\n",
			   queue->pending_prod,
			   queue->pending_cons,
			   nr_pending_reqs(queue));
		seq_printf(m, "dealloc prod %u dealloc cons %u dealloc_queue %u\n\n",
			   queue->dealloc_prod,
			   queue->dealloc_cons,
			   queue->dealloc_prod - queue->dealloc_cons);
	}

	if (rx_ring->sring) {
		struct xen_netif_rx_sring *sring = rx_ring->sring;

		seq_printf(m, "RX: nr_ents %u\n", rx_ring->nr_ents);
		seq_printf(m, "req prod %u (%d) cons %u (%d) event %u (%d)\n",
			   sring->req_prod,
			   sring->req_prod - sring->rsp_prod,
			   rx_ring->req_cons,
			   rx_ring->req_cons - sring->rsp_prod,
			   sring->req_event,
			   sring->req_event - sring->rsp_prod);
		seq_printf(m, "rsp prod %u (base) pvt %u (%d) event %u (%d)\n\n",
			   sring->rsp_prod,
			   rx_ring->rsp_prod_pvt,
			   rx_ring->rsp_prod_pvt - sring->rsp_prod,
			   sring->rsp_event,
			   sring->rsp_event - sring->rsp_prod);
	}

	seq_printf(m, "NAPI state: %lx NAPI weight: %d TX queue len %u\n"
		   "Credit timer_pending: %d, credit: %lu, usec: %lu\n"
		   "remaining: %lu, expires: %lu, now: %lu\n",
		   queue->napi.state, queue->napi.weight,
		   skb_queue_len(&queue->tx_queue),
		   timer_pending(&queue->credit_timeout),
		   queue->credit_bytes,
		   queue->credit_usec,
		   queue->remaining_credit,
		   queue->credit_timeout.expires,
		   jiffies);

	dev_queue = netdev_get_tx_queue(queue->vif->dev, queue->id);

	seq_printf(m, "\nRx internal queue: len %u max %u pkts %u %s\n",
		   queue->rx_queue_len, queue->rx_queue_max,
		   skb_queue_len(&queue->rx_queue),
		   netif_tx_queue_stopped(dev_queue) ? "stopped" : "running");

	return 0;
}

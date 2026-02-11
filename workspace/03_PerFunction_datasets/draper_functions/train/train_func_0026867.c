qp_cleanup_queue_mutex(struct vmci_queue *produce_q,
				   struct vmci_queue *consume_q)
{
	if (produce_q->kernel_if->host) {
		produce_q->kernel_if->mutex = NULL;
		consume_q->kernel_if->mutex = NULL;
	}
}

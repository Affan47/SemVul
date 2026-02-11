xenvif_dealloc_kthread(void *data)
{
	struct xenvif_queue *queue = data;

	for (;;) {
		wait_event_interruptible(queue->dealloc_wq,
					 tx_dealloc_work_todo(queue) ||
					 xenvif_dealloc_kthread_should_stop(queue));
		if (xenvif_dealloc_kthread_should_stop(queue))
			break;

		xenvif_tx_dealloc_action(queue);
		cond_resched();
	}


	if (tx_dealloc_work_todo(queue))
		xenvif_tx_dealloc_action(queue);

	return 0;
}

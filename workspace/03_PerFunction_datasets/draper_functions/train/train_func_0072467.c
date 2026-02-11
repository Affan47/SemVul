setup_queues(struct nullb *nullb)
{
	nullb->queues = kzalloc(submit_queues * sizeof(struct nullb_queue),
								GFP_KERNEL);
	if (!nullb->queues)
		return -ENOMEM;

	nullb->nr_queues = 0;
	nullb->queue_depth = hw_queue_depth;

	return 0;
}

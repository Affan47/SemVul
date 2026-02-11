dmatest_add_threads(struct dmatest_info *info,
		struct dmatest_chan *dtc, enum dma_transaction_type type)
{
	struct dmatest_params *params = &info->params;
	struct dmatest_thread *thread;
	struct dma_chan *chan = dtc->chan;
	char *op;
	unsigned int i;

	if (type == DMA_MEMCPY)
		op = "copy";
	else if (type == DMA_XOR)
		op = "xor";
	else if (type == DMA_PQ)
		op = "pq";
	else
		return -EINVAL;

	for (i = 0; i < params->threads_per_chan; i++) {
		thread = kzalloc(sizeof(struct dmatest_thread), GFP_KERNEL);
		if (!thread) {
			pr_warn("No memory for %s-%s%u\n",
				dma_chan_name(chan), op, i);
			break;
		}
		thread->info = info;
		thread->chan = dtc->chan;
		thread->type = type;
		thread->test_done.wait = &thread->done_wait;
		init_waitqueue_head(&thread->done_wait);
		smp_wmb();
		thread->task = kthread_create(dmatest_func, thread, "%s-%s%u",
				dma_chan_name(chan), op, i);
		if (IS_ERR(thread->task)) {
			pr_warn("Failed to create thread %s-%s%u\n",
				dma_chan_name(chan), op, i);
			kfree(thread);
			break;
		}


		get_task_struct(thread->task);
		list_add_tail(&thread->node, &dtc->threads);
		wake_up_process(thread->task);
	}

	return i;
}

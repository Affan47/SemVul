__blk_complete_request(struct request *req)
{
	int ccpu, cpu;
	struct request_queue *q = req->q;
	unsigned long flags;
	bool shared = false;

	BUG_ON(!q->softirq_done_fn);

	local_irq_save(flags);
	cpu = smp_processor_id();


	if (req->cpu != -1) {
		ccpu = req->cpu;
		if (!test_bit(QUEUE_FLAG_SAME_FORCE, &q->queue_flags))
			shared = cpus_share_cache(cpu, ccpu);
	} else
		ccpu = cpu;


	if (ccpu == cpu || shared) {
		struct list_head *list;
do_local:
		list = this_cpu_ptr(&blk_cpu_done);
		list_add_tail(&req->ipi_list, list);


		if (list->next == &req->ipi_list)
			raise_softirq_irqoff(BLOCK_SOFTIRQ);
	} else if (raise_blk_irq(ccpu, req))
		goto do_local;

	local_irq_restore(flags);
}

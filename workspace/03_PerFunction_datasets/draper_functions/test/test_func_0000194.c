amd_sched_entity_init(struct amd_gpu_scheduler *sched,
			  struct amd_sched_entity *entity,
			  struct amd_sched_rq *rq,
			  uint32_t jobs)
{
	int r;

	if (!(sched && entity && rq))
		return -EINVAL;

	memset(entity, 0, sizeof(struct amd_sched_entity));
	INIT_LIST_HEAD(&entity->list);
	entity->rq = rq;
	entity->sched = sched;

	spin_lock_init(&entity->queue_lock);
	r = kfifo_alloc(&entity->job_queue, jobs * sizeof(void *), GFP_KERNEL);
	if (r)
		return r;

	atomic_set(&entity->fence_seq, 0);
	entity->fence_context = fence_context_alloc(1);

	return 0;
}

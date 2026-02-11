__queue_work(int cpu, struct workqueue_struct *wq,
			 struct work_struct *work)
{
	struct pool_workqueue *pwq;
	struct worker_pool *last_pool;
	struct list_head *worklist;
	unsigned int work_flags;
	unsigned int req_cpu = cpu;


	WARN_ON_ONCE(!irqs_disabled());

	debug_work_activate(work);


	if (unlikely(wq->flags & __WQ_DRAINING) &&
	    WARN_ON_ONCE(!is_chained_work(wq)))
		return;
retry:
	if (req_cpu == WORK_CPU_UNBOUND)
		cpu = raw_smp_processor_id();


	if (!(wq->flags & WQ_UNBOUND))
		pwq = per_cpu_ptr(wq->cpu_pwqs, cpu);
	else
		pwq = unbound_pwq_by_node(wq, cpu_to_node(cpu));


	last_pool = get_work_pool(work);
	if (last_pool && last_pool != pwq->pool) {
		struct worker *worker;

		spin_lock(&last_pool->lock);

		worker = find_worker_executing_work(last_pool, work);

		if (worker && worker->current_pwq->wq == wq) {
			pwq = worker->current_pwq;
		} else {

			spin_unlock(&last_pool->lock);
			spin_lock(&pwq->pool->lock);
		}
	} else {
		spin_lock(&pwq->pool->lock);
	}


	if (unlikely(!pwq->refcnt)) {
		if (wq->flags & WQ_UNBOUND) {
			spin_unlock(&pwq->pool->lock);
			cpu_relax();
			goto retry;
		}

		WARN_ONCE(true, "workqueue: per-cpu pwq for %s on cpu%d has 0 refcnt",
			  wq->name, cpu);
	}


	trace_workqueue_queue_work(req_cpu, pwq, work);

	if (WARN_ON(!list_empty(&work->entry))) {
		spin_unlock(&pwq->pool->lock);
		return;
	}

	pwq->nr_in_flight[pwq->work_color]++;
	work_flags = work_color_to_flags(pwq->work_color);

	if (likely(pwq->nr_active < pwq->max_active)) {
		trace_workqueue_activate_work(work);
		pwq->nr_active++;
		worklist = &pwq->pool->worklist;
	} else {
		work_flags |= WORK_STRUCT_DELAYED;
		worklist = &pwq->delayed_works;
	}

	insert_work(pwq, work, worklist, work_flags);

	spin_unlock(&pwq->pool->lock);
}

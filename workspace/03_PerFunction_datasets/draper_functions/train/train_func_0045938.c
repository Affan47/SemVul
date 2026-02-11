mem_cgroup_begin_page_stat(struct page *page)
{
	struct mem_cgroup *memcg;
	unsigned long flags;


	rcu_read_lock();

	if (mem_cgroup_disabled())
		return NULL;
again:
	memcg = page->mem_cgroup;
	if (unlikely(!memcg))
		return NULL;

	if (atomic_read(&memcg->moving_account) <= 0)
		return memcg;

	spin_lock_irqsave(&memcg->move_lock, flags);
	if (memcg != page->mem_cgroup) {
		spin_unlock_irqrestore(&memcg->move_lock, flags);
		goto again;
	}


	memcg->move_lock_task = current;
	memcg->move_lock_flags = flags;

	return memcg;
}

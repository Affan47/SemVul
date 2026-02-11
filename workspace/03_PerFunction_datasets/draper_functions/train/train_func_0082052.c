shutdown_cache(struct kmem_cache *s,
		struct list_head *release, bool *need_rcu_barrier)
{
	if (__kmem_cache_shutdown(s) != 0)
		return -EBUSY;

	if (s->flags & SLAB_DESTROY_BY_RCU)
		*need_rcu_barrier = true;

	list_move(&s->list, release);
	return 0;
}

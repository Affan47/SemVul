update_memcg_params(struct kmem_cache *s, int new_array_size)
{
	struct memcg_cache_array *old, *new;

	if (!is_root_cache(s))
		return 0;

	new = kzalloc(sizeof(struct memcg_cache_array) +
		      new_array_size * sizeof(void *), GFP_KERNEL);
	if (!new)
		return -ENOMEM;

	old = rcu_dereference_protected(s->memcg_params.memcg_caches,
					lockdep_is_held(&slab_mutex));
	if (old)
		memcpy(new->entries, old->entries,
		       memcg_nr_cache_ids * sizeof(void *));

	rcu_assign_pointer(s->memcg_params.memcg_caches, new);
	if (old)
		kfree_rcu(old, rcu);
	return 0;
}

slab_pre_alloc_hook(struct kmem_cache *s,
						     gfp_t flags)
{
	flags &= gfp_allowed_mask;
	lockdep_trace_alloc(flags);
	might_sleep_if(gfpflags_allow_blocking(flags));

	if (should_failslab(s->object_size, flags, s->flags))
		return NULL;

	return memcg_kmem_get_cache(s, flags);
}

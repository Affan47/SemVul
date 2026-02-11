__memcg_kmem_put_cache(struct kmem_cache *cachep)
{
	if (!is_root_cache(cachep))
		css_put(&cachep->memcg_params.memcg->css);
}

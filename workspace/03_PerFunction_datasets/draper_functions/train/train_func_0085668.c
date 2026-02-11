prune_base_data(struct base_data *retain)
{
	struct base_data *b;
	for (b = base_cache;
	     base_cache_used > delta_base_cache_limit && b;
	     b = b->child) {
		if (b->data && b != retain)
			free_base_data(b);
	}
}

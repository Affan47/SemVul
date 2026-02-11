isalloc_validate(const void *ptr)
{
	arena_chunk_t *chunk;

	if (ptr == NULL)
		return (0);

	chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(ptr);
	if (chunk != ptr) {
		arena_t *arena;
		unsigned i;

		if (narenas > 1) {


			malloc_spin_lock(&arenas_lock);
			malloc_spin_unlock(&arenas_lock);
		}

		for (i = 0; i < narenas; i++) {
			arena = arenas[i];
			if (arena != NULL) {

				malloc_spin_lock(&arena->lock);
				if (RB_FIND(arena_chunk_tree_s, &arena->chunks,
				    chunk) == chunk) {
					malloc_spin_unlock(&arena->lock);


					assert(chunk->arena->magic ==
					    ARENA_MAGIC);
					return (arena_salloc(ptr));
				}
				malloc_spin_unlock(&arena->lock);
			}
		}
		return (0);
	} else {
		size_t ret;
		extent_node_t *node;
		extent_node_t key;


		key.addr = (void *)chunk;
		malloc_mutex_lock(&huge_mtx);
		node = RB_FIND(extent_tree_ad_s, &huge, &key);
		if (node != NULL)
			ret = node->size;
		else
			ret = 0;
		malloc_mutex_unlock(&huge_mtx);
		return (ret);
	}
}

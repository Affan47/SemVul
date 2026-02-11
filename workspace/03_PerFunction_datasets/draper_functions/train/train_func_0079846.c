chunk_record(extent_tree_t *chunks_szad, extent_tree_t *chunks_ad, void *chunk,
    size_t size)
{
	bool unzeroed;
	extent_node_t *xnode, *node, *prev, key;

	unzeroed = pages_purge(chunk, size);


	xnode = base_node_alloc();

	malloc_mutex_lock(&chunks_mtx);
	key.addr = (void *)((uintptr_t)chunk + size);
	node = extent_tree_ad_nsearch(chunks_ad, &key);

	if (node != NULL && node->addr == key.addr) {


		extent_tree_szad_remove(chunks_szad, node);
		node->addr = chunk;
		node->size += size;
		node->zeroed = (node->zeroed && (unzeroed == false));
		extent_tree_szad_insert(chunks_szad, node);
		if (xnode != NULL)
			base_node_dealloc(xnode);
	} else {

		if (xnode == NULL) {


			malloc_mutex_unlock(&chunks_mtx);
			return;
		}
		node = xnode;
		node->addr = chunk;
		node->size = size;
		node->zeroed = (unzeroed == false);
		extent_tree_ad_insert(chunks_ad, node);
		extent_tree_szad_insert(chunks_szad, node);
	}


	prev = extent_tree_ad_prev(chunks_ad, node);
	if (prev != NULL && (void *)((uintptr_t)prev->addr + prev->size) ==
	    chunk) {


		extent_tree_szad_remove(chunks_szad, prev);
		extent_tree_ad_remove(chunks_ad, prev);

		extent_tree_szad_remove(chunks_szad, node);
		node->addr = prev->addr;
		node->size += prev->size;
		node->zeroed = (node->zeroed && prev->zeroed);
		extent_tree_szad_insert(chunks_szad, node);

		base_node_dealloc(prev);
	}
	malloc_mutex_unlock(&chunks_mtx);
}

node_cache_flush(btree* bt)
{
    int i, size = bt->cache.size;
    int result = 0;

    for (i=0; i < size; i++)
    {
	node_entry* e = &bt->cache.entries[i];
	if(e->index && (e->flags & NODE_DIRTY))
	    if (node_cache_flush_node(bt, i))
		result = -1;
    }
    return result;
}

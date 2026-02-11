node_cache_init(node_cache* cache, btree* tree, int size)
{
    int nodebufsize;
    char * buf;

    cache->size		= size;
    cache->currindex	= 0;
    nodebufsize = tree->head.node_size + sizeof(node_buf);
    buf = malloc(size *(sizeof(node_entry) + nodebufsize));
    if (!buf)
	return -1;
    cache -> nodebufsize = nodebufsize;
    cache -> entries = (node_entry*) buf;
    cache -> buffers = (char*) &cache->entries[size];
    bzero(cache->entries, size*sizeof(node_entry));
    return 0;
}

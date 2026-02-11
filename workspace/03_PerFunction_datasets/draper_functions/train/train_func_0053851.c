node_cache_load_buf
    (btree* bt, node_cache* cache, int index, UInt16 node_index, int flags)
{
    node_buf	*result	    = node_buf_get(cache ,index);
    UInt16	blkpernode  = bt->blkpernode;
    UInt16	nodeperblk  = bt->nodeperblk;
    node_entry	*e	    = &cache->entries[index];
    UInt32	block;
    void	*p;

    if (blkpernode)
    {
	block = node_index * blkpernode;
	p     = volume_readfromfork(bt->vol, result->node, bt->fork,
		     block, blkpernode, HFSP_EXTENT_DATA, bt->cnid);
	if (!p)
	    return NULL;

	btree_readnode(&result->desc, p);
    }
    else
    {
	char buf[bt->vol->blksize];

	UInt16 node_size = bt->head.node_size;
	UInt16 offset = node_index % nodeperblk * node_size;
	block = node_index / nodeperblk;
	p     = volume_readfromfork(bt->vol, buf, bt->fork,
		     block, 1, HFSP_EXTENT_DATA, bt->cnid);
	if (p != buf)
	    return NULL;
	p = &buf[offset];
	memcpy(&result->node, p , node_size);
	btree_readnode(&result->desc, p);

    }

    result->index   = node_index;

    e -> priority   = result->desc.height * DEPTH_FACTOR;
    e -> index	    = node_index;
    e -> flags	    = flags;
    return result;
}

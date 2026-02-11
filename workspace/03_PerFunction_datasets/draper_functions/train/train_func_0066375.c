btree_write_node(btree* bt, int index, char* nodebuf)
{
    UInt16	blkpernode  = bt->blkpernode;
    UInt16	nodeperblk  = bt->nodeperblk;

    if (blkpernode)
    {
	return volume_writetofork(bt->vol, nodebuf, bt->fork,
		     index * blkpernode, blkpernode, HFSP_EXTENT_DATA, bt->cnid);
    }
    else
    {
	char buf[bt->vol->blksize];

	UInt16	node_size = bt->head.node_size;
	UInt16	offset    = (index % nodeperblk) * node_size;
	int	block     = index / nodeperblk;


	void* p  = volume_readfromfork(bt->vol, buf, bt->fork,
		     block, 1, HFSP_EXTENT_DATA, bt->cnid);
	if (p != buf)
	    return -1;
	p = &nodebuf[offset];
	memcpy(p, nodebuf, node_size);
	if (volume_writetofork(bt->vol, buf, bt->fork,
		     block, 1, HFSP_EXTENT_DATA, bt->cnid))
	    return -1;
    }
    return 0;
}

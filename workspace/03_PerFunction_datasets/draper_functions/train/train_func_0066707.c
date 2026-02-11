fscheck_record_next(record* r, int* fsckerr)
{
    btree*	tree	= r->tree;
    UInt16	index	= r->keyind +1;
    UInt32	parent;
    node_buf*	buf	= fscheck_prepare_next(
	    tree, r->node_index, &index, fsckerr);

    if (!buf)
	return ENOENT;

    parent = r->key.parent_cnid;

    if (fscheck_record_init(r, tree, buf, index))
    {
	printf("Unable to read record %d in node %d"
		,index, r->node_index);
	return -1;
    }

    return 0;
}

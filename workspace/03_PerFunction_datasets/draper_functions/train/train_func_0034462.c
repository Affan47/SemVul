dgl_initialize_V1(dglGraph_s * pgraph)
{
    if (pgraph->pNodeTree == NULL)
	pgraph->pNodeTree =
	    avl_create(dglTreeNodeCompare, NULL, dglTreeGetAllocator());
    if (pgraph->pNodeTree == NULL) {
	pgraph->iErrno = DGL_ERR_MemoryExhausted;
	return -pgraph->iErrno;
    }
    pgraph->pEdgeTree = NULL;
    return 0;
}

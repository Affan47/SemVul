doCleanup (Agraph_t* g)
{
    Agnode_t *n;
    ndata *nd;

    for (n = agfstnode(g); n; n =  agnxtnode(g, n)) {
	nd = nData(n);
	nd->ine = NULL;
	nd->iu.integer = 0;
    }
}

dglNode_T_Initialize(dglNodeTraverser_s * pT, dglGraph_s * pGraph)
{
    switch (pGraph->Version) {
    case 1:
	return dgl_node_t_initialize_V1(pGraph, pT);
#ifdef DGL_V2
    case 2:
    case 3:
	return dgl_node_t_initialize_V2(pGraph, pT);
#endif
    }
    pGraph->iErrno = DGL_ERR_BadVersion;
    return -pGraph->iErrno;
}

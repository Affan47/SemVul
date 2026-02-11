dglNodeGet_OutDegree(dglGraph_s * pGraph, dglInt32_t * pnNode)
{
    dglInt32_t *poutedgeset;

    pGraph->iErrno = 0;
    if (pnNode) {
	switch (pGraph->Version) {
	case 1:
	    if (DGL_NODE_STATUS_v1(pnNode) & DGL_NS_ALONE)
		return 0;
	    poutedgeset = dglNodeGet_OutEdgeset(pGraph, pnNode);
	    if (poutedgeset)
		return DGL_EDGESET_EDGECOUNT_v1(poutedgeset);
	    return 0;
#ifdef DGL_V2
	case 2:
	    if (DGL_NODE_STATUS_v2(pnNode) & DGL_NS_ALONE)
		return 0;
	    poutedgeset = dglNodeGet_OutEdgeset(pGraph, pnNode);
	    if (poutedgeset)
		return DGL_EDGESET_EDGECOUNT_v2(poutedgeset);
	    return 0;
	case 3:
	    return dglNodeGet_Valence(pGraph, pnNode);
#endif
	}
	pGraph->iErrno = DGL_ERR_BadVersion;
	return 0;
    }
    pGraph->iErrno = DGL_ERR_UnexpectedNullPointer;
    return 0;
}

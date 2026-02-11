addEdge          (pANTLR3_TOPO topo, ANTLR3_UINT32 edge, ANTLR3_UINT32 dependency)
{
    ANTLR3_UINT32   i;
    ANTLR3_UINT32   maxEdge;
    pANTLR3_BITSET  edgeDeps;

    if (edge>dependency)
    {
        maxEdge = edge;
    }
    else
    {
        maxEdge = dependency;
    }


    if (topo->edges == NULL)
    {


        topo->edges = ANTLR3_CALLOC(sizeof(pANTLR3_BITSET) * (maxEdge + 1), 1);
        if (topo->edges == NULL)
        {
            return;
        }


        topo->limit = maxEdge + 1;
    }
    else if (topo->limit <= maxEdge)
    {


        topo->edges = ANTLR3_REALLOC(topo->edges, sizeof(pANTLR3_BITSET) * (maxEdge + 1));
        if (topo->edges == NULL)
        {
            return;
        }


        for (i = topo->limit; i <= maxEdge; i++)
        {
            *((topo->edges) + i) = NULL;
        }


        topo->limit = maxEdge + 1;
    }


    if  (edge == dependency)
    {
        return;
    }


    edgeDeps = *((topo->edges) + edge);

    if  (edgeDeps == NULL)
    {


        edgeDeps                = antlr3BitsetNew(0);
        *((topo->edges) + edge) = edgeDeps;
        if (edgeDeps == NULL )
        {
            return;
        }
    }


    edgeDeps->add(edgeDeps, dependency);


    return;
}

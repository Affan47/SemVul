GetEdgeToGroupVertex( BN_STRUCT *pBNS, Vertex v1, AT_NUMB type)
{
    if ( v1 < pBNS->num_atoms ) {
        Vertex      v2;
        BNS_EDGE   *pEdge1;
        BNS_VERTEX *pVert1 = pBNS->vert+v1;
        int         i      = pVert1->num_adj_edges-1;

        while( 0 <= i ) {
            pEdge1 = pBNS->edge + pVert1->iedge[i];
            v2 = pEdge1->neighbor12 ^ v1;
            if ( pBNS->vert[v2].type == type ) {
                return IS_FORBIDDEN(pEdge1->forbidden, pBNS)? NO_VERTEX : pVert1->iedge[i];
            }
            i --;
        }
        return NO_VERTEX;
    } else
    if ( v1 < pBNS->num_vertices ) {
        return NO_VERTEX;
    }
    return BNS_VERT_EDGE_OVFL;
}

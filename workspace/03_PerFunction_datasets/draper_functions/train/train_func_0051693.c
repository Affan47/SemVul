bIgnoreVertexNonTACN_atom( BN_STRUCT* pBNS, Vertex u, Vertex v )
{
    int    i, degree, ret, u_is_taut=0, num_allowed=0, num_found_groups=0;
    Vertex w;
    EdgeIndex ivw;
    if ( !pBNS->type_TACN || u <= 1 || v <= 1 ||
         (pBNS->vert[v/2-1].type & pBNS->type_TACN) ) {
        return 0;
    }
    if ( !pBNS->type_T || !pBNS->type_CN )
        return 0;
    if ( (u_is_taut  = (pBNS->vert[u/2-1].type & pBNS->type_T)  == pBNS->type_T) ||
         (             (pBNS->vert[u/2-1].type & pBNS->type_CN) == pBNS->type_CN)  ) {

        degree = GetVertexDegree( pBNS, v );
        for ( i = 0; i < degree; i ++ ) {

            w = GetVertexNeighbor( pBNS, v, i, &ivw );
            if ( w == NO_VERTEX || w <= 1 ) {
                continue;
            }
            if ( w != u && (ret = rescap(pBNS, v, w, ivw)) > 0 ) {
                num_allowed ++;
                if ( (u_is_taut? ((pBNS->vert[w/2-1].type & pBNS->type_CN) == pBNS->type_CN) :
                                 ((pBNS->vert[w/2-1].type & pBNS->type_T)  == pBNS->type_T ) ) ) {
                    num_found_groups ++;
                }
            }
        }
        if ( num_found_groups && num_allowed == 1 ) {
            return 1;
        }

    }
    return 0;
}

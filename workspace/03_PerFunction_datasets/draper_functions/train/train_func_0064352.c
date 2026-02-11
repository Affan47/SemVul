RestoreRadicalsOnly( BN_STRUCT *pBNS, BN_DATA *pBD, inp_ATOM *at )
{
    BNS_EDGE   *e;
    EdgeIndex   ie;
    BNS_VERTEX *p1, *p2;
    Vertex      v1, v2;
    int         i, delta, rad;
    int         p1_num_adj_edges, p2_num_adj_edges;

    for ( i = pBD->nNumRadEdges-1; 0 <= i; i -- ) {
        ie = pBD->RadEdges[i];
        if ( ie < 0 || ie >= pBNS->num_edges ) {
            goto error_exit;
        }
        e = pBNS->edge + ie;
        v1 = e->neighbor1;
        v2 = e->neighbor12 ^ v1;
        if ( v1 < 0 || v1 >= pBNS->num_atoms ||
             v2 < pBNS->num_atoms || v2 >= pBNS->num_vertices ) {
            goto error_exit;
        }
        p1 = pBNS->vert + v1;
        p2 = pBNS->vert + v2;

        p1_num_adj_edges = e->neigh_ord[0];
        p2_num_adj_edges = e->neigh_ord[1];

        if ( p2->iedge[p2_num_adj_edges] != ie ||
             p1->iedge[p1_num_adj_edges] != ie ) {
            goto error_exit;
        }

        if ( at && v1 < pBNS->num_atoms ) {
            delta = p1->st_edge.cap - p1->st_edge.flow + e->flow;
            rad   = at[v1].radical;
            switch( delta ) {
            case 0:
                if ( rad == RADICAL_DOUBLET )
                    rad = 0;
                break;
            case 1:
                if ( rad != RADICAL_DOUBLET )
                    rad = RADICAL_DOUBLET;
            }
            at[v1].radical = rad;
        }
    }
    return 0;
error_exit:
    return BNS_PROGRAM_ERR;
}

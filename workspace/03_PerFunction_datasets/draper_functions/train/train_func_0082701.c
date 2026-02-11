nTautEndpointEdgeCap( inp_ATOM *at, VAL_AT *pVA, int i )
{


    int j, k, nEdgeCap, bonds_valence, stereo_bond_excess_valence;
    MY_CONST C_NODE *pCN = pVA[i].cnListIndex>0? cnList[pVA[i].cnListIndex-1].pCN:NULL;


    nEdgeCap = pVA[i].cInitFreeValences;

    if ( pCN ) {
        nEdgeCap += pCN[0].v.cap - pCN[0].v.flow;
    }


    for ( stereo_bond_excess_valence=0, j = 0; j < MAX_NUM_STEREO_BONDS && at[i].sb_parity[j]; j ++ ) {
        k = at[i].sb_ord[j];
        if ( at[i].bond_type[k] < BOND_TYPE_TRIPLE ) {
            stereo_bond_excess_valence += at[i].bond_type[k] - BOND_TYPE_SINGLE;
        }
    }


    bonds_valence = (at[i].chem_bonds_valence - at[i].valence) - stereo_bond_excess_valence;


    if ( bonds_valence >= 0 ) {
        nEdgeCap += bonds_valence;
    } else {
        nEdgeCap = RI_ERR_PROGR;
    }
    return nEdgeCap;
}

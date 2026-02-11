HalfStereoBondParity( sp_ATOM *at, int at_no1, int i_sb_neigh, const AT_RANK *nRank )
{


    int i, j, k, iNeigh, parity, at1_parity, at_no2;
    AT_RANK r[MAX_NUM_STEREO_BOND_NEIGH];

    if ( at[at_no1].valence > MAX_NUM_STEREO_BOND_NEIGH || ( at1_parity = at[at_no1].parity ) <= 0 ) {
        return 0;
    }
    if ( !PARITY_WELL_DEF( at1_parity ) ) {
        if ( PARITY_KNOWN( at1_parity ) ) {
            return at1_parity;
        }
        return -at1_parity;
    }
    if ( 0 > i_sb_neigh || i_sb_neigh >= MAX_NUM_STEREO_BOND_NEIGH ) {
        return CT_STEREOBOND_ERROR;
    }
    for ( i = 0; i <= i_sb_neigh; i ++ ) {
        if ( !at[at_no1].stereo_bond_neighbor[i] ) {
            return CT_STEREOBOND_ERROR;
        }
    }
    at_no2 = at[at_no1].neighbor[(int)at[at_no1].stereo_bond_ord[i_sb_neigh]];
    memset( r, 0, sizeof( r ) );
    for ( i = j = 0, iNeigh = -1; i < at[at_no1].valence; i ++ ) {
        if ( (k = (int)at[at_no1].neighbor[i]) == at_no2 ) {
            iNeigh = i;
        } else {
            r[j++] = nRank[k];
        }
    }
    if ( iNeigh < 0 || iNeigh != at[at_no1].stereo_bond_ord[i_sb_neigh] ) {
        return CT_STEREOBOND_ERROR;
    }
    if ( j > 0 && !r[0] || j > 1 && !r[1] )
        return 0;

    if ( j == 2 && r[0] == r[1] || iNeigh < 0 ) {
        parity = AB_PARITY_CALC;
    } else {
        parity = 2 - (at[at_no1].parity + iNeigh + (r[1] < r[0])) % 2;
    }
    return parity;
}

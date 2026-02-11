bIsUnsatCarbonInASmallRing( inp_ATOM *at2, VAL_AT *pVA, int iat, BFS_Q *pbfsq, int min_ring_size )
{
    int j, nCurRingSize, nMinRingSize;
    if ( min_ring_size < 5 ) {

        if ( at2[iat].valence == 2 &&
             pVA[iat].cMinRingSize <= 5 &&
             at2[iat].chem_bonds_valence == 4 ) {
            return 1;
        }
    } else {
        if ( at2[iat].valence == 2 &&
             pVA[iat].cMinRingSize &&
             pVA[iat].cMinRingSize <= min_ring_size &&
             at2[iat].chem_bonds_valence == 3 ) {
            return 1;
        }
        nCurRingSize = nMinRingSize = min_ring_size+1;
        if ( (at2[iat].valence == 2 || at2[iat].valence == 3) &&
             at2[iat].chem_bonds_valence == at2[iat].valence+1 ) {
            for ( j = 0; j < at2[iat].valence; j ++ ) {
                nCurRingSize = is_bond_in_Nmax_memb_ring( at2, iat, j, pbfsq->q,
                                             pbfsq->nAtomLevel,
                                             pbfsq->cSource, (AT_RANK)nMinRingSize  );
                if ( 0 < nCurRingSize && nCurRingSize < nMinRingSize ) {
                    nMinRingSize = nCurRingSize;
                }
            }
            return (0 <= nCurRingSize)? (nMinRingSize <= min_ring_size) : nCurRingSize;
        }
    }
    return 0;
}

MarkKnownEqualStereoCenterParities( sp_ATOM *at, int num_atoms,
                                        const AT_RANK *nRank, const AT_RANK *nAtomNumber )
{
    int i, j1, k, num_centers, iMax, bDifferentParities;
    AT_RANK nAtomRank;
    int  parity, parity_k;
    num_centers = 0;
    for ( i = 0; i < num_atoms; i ++ ) {
        if ( !at[i].parity || at[i].stereo_bond_neighbor[0] ) {
            continue;
        }
        if ( at[i].bHasStereoOrEquToStereo ) {
            continue;
        }
        if (  (at[i].stereo_atom_parity & KNOWN_PARITIES_EQL) ) {
            continue;
        }
        parity    = PARITY_VAL(at[i].stereo_atom_parity);
        if ( parity == AB_PARITY_NONE ) {
            continue;
        }
        nAtomRank = nRank[i];
        bDifferentParities = -1;

        for ( iMax = (int)nAtomRank-1, j1 = 0; j1 <= iMax && nAtomRank==nRank[k=(int)nAtomNumber[iMax-j1]]; j1 ++ ) {

            parity_k = PARITY_VAL(at[k].stereo_atom_parity);
            if ( parity_k != parity ) {
                bDifferentParities = 1;
            } else
            if ( parity_k == parity && bDifferentParities < 0 ) {
                bDifferentParities = 0;
            }
            if ( !parity_k ) {
                at[k].bHasStereoOrEquToStereo = 2;
            } else
            if ( !at[k].bHasStereoOrEquToStereo ) {
                at[k].bHasStereoOrEquToStereo = 1;
            }
        }
        if ( 0 == bDifferentParities && PARITY_KNOWN( parity ) ) {
            for ( iMax = (int)nAtomRank-1, j1 = 0; j1 <= iMax && nAtomRank==nRank[k=(int)nAtomNumber[iMax-j1]]; j1 ++ ) {

                at[k].stereo_atom_parity |= KNOWN_PARITIES_EQL;
                num_centers ++;
            }
        }
    }
    return num_centers;
}

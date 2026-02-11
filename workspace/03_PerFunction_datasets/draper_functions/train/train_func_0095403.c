SetUseAtomForStereo( S_CHAR *bAtomUsedForStereo, sp_ATOM *at, int num_atoms )
{
    int i, k;
    memset( bAtomUsedForStereo, 0, sizeof( bAtomUsedForStereo[0] )*num_atoms );
    for ( i = 0; i < num_atoms; i ++ ) {
        if ( at[i].parity ) {
            for ( k = 0; k < MAX_NUM_STEREO_BONDS && at[i].stereo_bond_neighbor[k]; k ++ )
                ;
            bAtomUsedForStereo[i] = k? k : STEREO_AT_MARK;
        }
    }
}

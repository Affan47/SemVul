SetHalfStereoBondIllDefPariy( sp_ATOM *at, int jn,  int k1 , int new_parity )
{
    int parity;
    if ( k1 < MAX_NUM_STEREO_BOND_NEIGH && at[jn].stereo_bond_neighbor[k1] ) {
        parity = at[jn].stereo_bond_parity[k1] ^ PARITY_VAL(at[jn].stereo_bond_parity[k1]);
        at[jn].stereo_bond_parity[k1] = parity | PARITY_VAL(new_parity);
        at[jn].parity = PARITY_VAL(new_parity);
        return 1;
    }
    return 0;
}

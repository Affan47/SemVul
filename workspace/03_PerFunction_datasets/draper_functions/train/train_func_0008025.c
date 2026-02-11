DisconnectMetalSalt( inp_ATOM *at, int i )
{
    int k, iO;

    for ( k = 0; k < at[i].valence; k ++ ) {
        iO = at[i].neighbor[k];
        if ( at[iO].valence == 2 ) {
            if ( at[iO].neighbor[0] == i ) {

                at[iO].neighbor[0]    = at[iO].neighbor[1];
                at[iO].bond_stereo[0] = at[iO].bond_stereo[1];
                at[iO].bond_type[0]   = at[iO].bond_type[1];
            }

            at[iO].neighbor[1]    = 0;
            at[iO].bond_stereo[1] = 0;
            at[iO].bond_type[1]   = 0;
        } else {

            at[iO].neighbor[0]    = 0;
            at[iO].bond_stereo[0] = 0;
            at[iO].bond_type[0]   = 0;
        }

        at[iO].charge = -1;

        at[iO].valence --;
        at[iO].chem_bonds_valence --;


        at[i].neighbor[k]    = 0;
        at[i].bond_stereo[k] = 0;
        at[i].bond_type[k]   = 0;

        at[i].charge ++;
    }

    at[i].valence            = 0;
    at[i].chem_bonds_valence = 0;
    return k;
}

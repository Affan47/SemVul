GetOtherSaltType( inp_ATOM *at, int at_no, int *s_subtype )
{
    static int el_number_C  = 0;


    static int el_number_S  = 0;
    static int el_number_Se = 0;
    static int el_number_Te = 0;


    int type, endpoint_valence, bond_type, centerpoint;
    ENDPOINT_INFO eif;

    if ( at[at_no].valence != 1 || at[at_no].chem_bonds_valence != 1 ||
         1 != (at[at_no].num_H==1) + (at[at_no].charge==-1) ) {
        return -1;
    }

    if ( !el_number_S ) {
        el_number_C  = get_periodic_table_number( "C" );


        el_number_S  = get_periodic_table_number( "S" );
        el_number_Se = get_periodic_table_number( "Se" );
        el_number_Te = get_periodic_table_number( "Te" );
    }
    *s_subtype = 0;
    if ( !(at[at_no].el_number == el_number_S  ||
           at[at_no].el_number == el_number_Se ||
           at[at_no].el_number == el_number_Te ) ) {
        return -1;
    }

    type = 2;

    if ( !(endpoint_valence = nGetEndpointInfo( at, at_no, &eif )) ||
         eif.cMoveableCharge && !at[at_no].c_point || !eif.cDonor || eif.cAcceptor ) {
        return -1;
    } else {


        centerpoint = (int)at[at_no].neighbor[0];
        bond_type   = (int)at[at_no].bond_type[0] & BOND_TYPE_MASK;
        if ( at[centerpoint].el_number != el_number_C ||
             at[centerpoint].charge ||
             at[centerpoint].radical && at[centerpoint].radical != RADICAL_SINGLET ||
             at[centerpoint].valence != at[centerpoint].chem_bonds_valence ) {
            return -1;
        }
        if ( at[at_no].num_H == 1 ) {
            *s_subtype |= SALT_p_DONOR;
        } else
        if ( at[at_no].charge == -1 ) {
            *s_subtype |= SALT_p_ACCEPTOR;
        } else {
            return -1;
        }
    }
    return type;
}

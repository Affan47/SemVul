get_pVA_atom_type( VAL_AT *pVA, inp_ATOM *at, int iat, int bond_type )
{
    int type = 0, val;
    if ( pVA[iat].cNumValenceElectrons == 4 ) {
        if ( pVA[iat].cPeriodicRowNumber == 1 ) {
            type |= EL_TYPE_C;
        }
    } else
    if ( pVA[iat].cNumValenceElectrons == 6 ) {
        if ( pVA[iat].cPeriodicRowNumber == 1 ) {
            type |= EL_TYPE_O;
        } else
        if ( pVA[iat].cPeriodicRowNumber < 5 ) {
            type |= EL_TYPE_S;
        }
        if ( bond_type == BOND_TYPE_SINGLE &&
             (type & (EL_TYPE_O | EL_TYPE_S)) &&
             1 == nNoMetalBondsValence(at, iat ) &&
             1 == nNoMetalNumBonds(at, iat) ) {
            type |= EL_TYPE_OSt;
        }
    } else
    if ( pVA[iat].cNumValenceElectrons == 5 ) {
        if ( pVA[iat].cPeriodicRowNumber == 1 ) {
            type |= EL_TYPE_N;
        } else {
            type |= EL_TYPE_P;
        }
    } else
    if ( !is_el_a_metal(pVA[iat].cPeriodicNumber) ) {
        type |= EL_TYPE_X;
    }

    val = get_endpoint_valence( at[iat].el_number );
    if ( val && val > at[iat].valence && !at[iat].radical &&
         -1 <= at[iat].charge && at[iat].charge <= 0 &&
         val == at[iat].chem_bonds_valence - at[iat].charge + at[iat].num_H ) {
        type |= EL_TYPE_PT;
    }
    return type;
}

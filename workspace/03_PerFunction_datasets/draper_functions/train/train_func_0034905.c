SimpleAddAcidicProtons( inp_ATOM *at, int num_atoms, BN_AATG *pAATG, int num2add )
{
    int i, j, max_j=-1, mask, type, num_added;
    int num[AR_SIMPLE_STEPS+1], num_tot;

    for ( j = 0; AaTypMask[2*j]; j ++ ) {
        num[max_j = j] = 0;
    }

    for ( i = 0; i < num_atoms; i ++ ) {
        if ( at[i].charge==-1 &&  (type = GetAtomChargeType( at, i, NULL, &mask, 0 )) ) {
            for ( j = 0; j <= max_j; j ++ ) {
                if ( (type & AaTypMask[2*j]) && (mask && AaTypMask[2*j+1]) ) {
                    num[j]  ++;
                    break;
                }
            }
        }
    }
    for ( j = 0, num_tot = 0; j <= max_j; j ++ ) {
        if ( (num_tot += num[j]) >= num2add ) {
            max_j = j;
            break;
        }
    }
    if ( !num_tot ) {
        return 0;
    }
    for ( i = 0, num_added = 0; i < num_atoms && num_added < num2add; i ++ ) {
        if ( at[i].charge==-1 && (type = GetAtomChargeType( at, i, NULL, &mask, 0 )) ) {
            for ( j = 0; j <= max_j; j ++ ) {
                if ( num[j] && (type & AaTypMask[2*j]) && (mask && AaTypMask[2*j+1]) ) {
                    type = GetAtomChargeType( at, i, pAATG->nAtTypeTotals, &mask, 1 );
                    num[j]  --;
                    at[i].charge ++;
                    AddOrRemoveExplOrImplH( 1, at, num_atoms, (AT_NUMB)i, pAATG->t_group_info );

                    num_added ++;
                    type = GetAtomChargeType( at, i, pAATG->nAtTypeTotals, &mask, 0 );
                    break;
                }
            }
        }
    }


    return num_added;
}

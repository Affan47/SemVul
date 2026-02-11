are_alt_bonds( U_CHAR *bonds, int len )
{
    U_CHAR next_bond;
    int           i, bAnyBond, bTautBondPresent=BOND_ALTERN;
    if ( len < 2 || bonds[0] == BOND_TRIPLE || bonds[0] == BOND_ALT_13 ) {
        return 0;
    }
    next_bond = bonds[0]==BOND_SINGLE? BOND_DOUBLE : bonds[0]==BOND_DOUBLE? BOND_SINGLE : 0;
    if ( bonds[0] == BOND_TAUTOM ) {
        bTautBondPresent= BOND_TAUTOM;
        next_bond = 0;
    } else {
        next_bond = bonds[0]==BOND_SINGLE? BOND_DOUBLE : bonds[0]==BOND_DOUBLE? BOND_SINGLE : 0;
    }

    for ( i = 1; i < len; i ++ ) {
        if ( bonds[i] == BOND_TAUTOM ) {
            bTautBondPresent = BOND_TAUTOM;
            bAnyBond         = 1;
        } else {
            bAnyBond = (bonds[i] == BOND_ALTERN || bonds[i] == BOND_ALT12NS);
        }
        if ( next_bond ) {
            if ( bonds[i] == next_bond || bAnyBond ) {
                next_bond = (next_bond == BOND_SINGLE)? BOND_DOUBLE : BOND_SINGLE;
                continue;
            }
            return 0;
        } else
        if ( bonds[i] == BOND_SINGLE ) {
            next_bond = BOND_DOUBLE;
            continue;
        } else
        if ( bonds[i] == BOND_DOUBLE ) {
            next_bond = BOND_SINGLE;
            continue;
        } else
        if ( !bAnyBond ) {
            return 0;
        }
    }
    return !next_bond? bTautBondPresent :
           (next_bond == BOND_SINGLE)? BOND_DOUBLE : BOND_SINGLE;
}

SubtractOrChangeAtHChargeBNS( BN_STRUCT *pBNS, inp_ATOM *at, int num_atoms,
                                 int nAtTypeTotals[], S_CHAR *mark, T_GROUP_INFO *t_group_info, int bSubtract )
{
    int       pass, i, v0, v1, v2, ineigh1,  vLast, n, delta, ret, err = 0;
    BNS_EDGE *edge;
    int       nDeltaH, nDeltaCharge;
    int       mask, type;

    for ( pass = pBNS->num_altp-1, ret = 0; 0 <= pass; pass -- ) {

        pBNS->alt_path = pBNS->altp[pass];
        v1 = ALTP_START_ATOM(pBNS->alt_path);
        n  = ALTP_PATH_LEN(pBNS->alt_path);
        delta  = ALTP_DELTA(pBNS->alt_path);
        vLast = ALTP_END_ATOM(pBNS->alt_path);
        v0 = v2 = NO_VERTEX;

        for ( i = 0; i < n; i ++, delta = -delta, v0 = v1, v1 = v2 ) {
            ineigh1 = ALTP_THIS_ATOM_NEIGHBOR(pBNS->alt_path, i);

            edge = pBNS->edge + pBNS->vert[v1].iedge[ineigh1];


            v2 = edge->neighbor12 ^ v1;
            if ( v1 < num_atoms && (v0 >= num_atoms || v2 >= num_atoms) ) {
                nDeltaH = nDeltaCharge = 0;
                if ( v0 >= num_atoms ) {

                    if ( pBNS->vert[v0].type & BNS_VERT_TYPE_TGROUP ) {
                        nDeltaH -= delta;
                    } else
                    if ( pBNS->vert[v0].type & BNS_VERT_TYPE_C_GROUP ) {
                        nDeltaCharge += delta;
                    }
                }
                if ( v2 >= num_atoms ) {
                    if ( pBNS->vert[v2].type & BNS_VERT_TYPE_TGROUP ) {
                        nDeltaH += delta;
                    } else
                    if ( pBNS->vert[v2].type & BNS_VERT_TYPE_C_GROUP ) {
                        nDeltaCharge -= delta;
                    }
                }
                if ( nDeltaH || nDeltaCharge ) {
                    if ( bSubtract ) {
                        if ( !mark[v1] ) {

#if( FIX_NORM_BUG_ADD_ION_PAIR == 1 )
                            type   = GetAtomChargeType( at, v1, nAtTypeTotals, &mask, 2 );
#else
                            type   = GetAtomChargeType( at, v1, nAtTypeTotals, &mask, 1 );
#endif
                            ret ++;
                            mark[v1] ++;
                        }
                    } else {
                        at[v1].charge += nDeltaCharge;
                        if ( nDeltaH ) {
                            AddOrRemoveExplOrImplH( nDeltaH, at, num_atoms, (AT_NUMB)v1, t_group_info );
                        }
                        ret ++;
                    }
                }
            }
        }

        if ( v2 != vLast ) {
            err = BNS_PROGRAM_ERR;
        }
    }
    return err? err : ret;
}

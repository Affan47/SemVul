BnsAdjustFlowBondsRad( BN_STRUCT *pBNS, BN_DATA *pBD, inp_ATOM *at, int num_atoms )
{
    int  bError=0, nOrigDelta=0, ret, num_removed;

#if( CHECK_AROMBOND2ALT == 1 )
    char *pcValMinusBondsVal = NULL;
    int  i, nValMinusBondsVal, nAltBonds, bIgnore;


    for ( i = 0; i < num_atoms; i ++ ) {
        nValMinusBondsVal = (int)at[i].chem_bonds_valence - nBondsValenceInpAt( at+i, &nAltBonds, &bIgnore );
        bIgnore += (nAltBonds > 3);
        if ( !bIgnore && nValMinusBondsVal > 0 ) {
            if ( !pcValMinusBondsVal &&
                 !(pcValMinusBondsVal = (char *)inchi_calloc(num_atoms, sizeof(pcValMinusBondsVal[0])))) {
                bError = BNS_OUT_OF_RAM;
                goto exit_function;
            }

            pcValMinusBondsVal[i] = nValMinusBondsVal + (at[i].radical == RADICAL_DOUBLET);
        }
    }
#endif


    do {
        num_removed = 0;
        ret = RunBalancedNetworkSearch( pBNS, pBD, BNS_EF_CHNG_FLOW );
        if ( IS_BNS_ERROR( ret ) ) {
            bError = ret;
        } else {
            nOrigDelta += ret;
            num_removed = pBNS->num_altp;
            if ( ret > 0 ) {

                ret = SetBondsFromBnStructFlow( pBNS, at, num_atoms, BNS_EF_SAVE_ALL );
                if ( IS_BNS_ERROR( ret ) ) {
                    bError = ret;
                }
                ret = RestoreBnStructFlow( pBNS, BNS_EF_SAVE_ALL );
                if ( IS_BNS_ERROR( ret ) ) {
                    bError = ret;
                }
            }
            ReInitBnStructAltPaths( pBNS );
        }
    } while ( num_removed && num_removed == pBNS->max_altp && !bError );

#if( CHECK_AROMBOND2ALT == 1 )

    if ( !bError && pcValMinusBondsVal ) {
        for ( i = 0; i < num_atoms; i ++ ) {
            if ( !pcValMinusBondsVal[i] )
                continue;
            nValMinusBondsVal = (int)at[i].chem_bonds_valence - nBondsValenceInpAt( at+i, &nAltBonds, &bIgnore );
            if ( bIgnore ||
                 1 != (int)pcValMinusBondsVal[i] - (nValMinusBondsVal + (at[i].radical == RADICAL_DOUBLET)) ) {

                bError = BNS_ALTBOND_ERR;
                break;
            }
        }
    }

exit_function:
    if ( pcValMinusBondsVal ) inchi_free( pcValMinusBondsVal );
#endif

    return bError? bError : nOrigDelta;
}

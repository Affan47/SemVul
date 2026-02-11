MakeCtStringOld( AT_NUMB *LinearCT, int nLenCT, int bAddDelim,
                  char *szLinearCT, int nLen_szLinearCT, int nCtMode, int *bOverflow)
{

    int nLen = 0, len, i, bLessThanPrev, bOvfl = *bOverflow;
    AT_NUMB nMax = 0;
    char szValue[16];
    int   nValue, bNext = 0;

    if ( !( nCtMode & CT_MODE_ABC_NUMBERS ) && !bOvfl && bAddDelim ) {
        if ( nLen_szLinearCT > 1 ) {
            strcpy( szLinearCT, "," );
            nLen ++;
        } else {
            bOvfl = 1;
        }
    }
    if ( !bOvfl ) {
        for ( i = 0; i < nLenCT && nLen < nLen_szLinearCT; i ++ ) {
            bLessThanPrev = 0;
            if ( !(nCtMode & CT_MODE_NO_ORPHANS) || ((bLessThanPrev=LinearCT[i] < nMax) ||
                  i+1 < nLenCT && LinearCT[i+1] < (nMax=LinearCT[i])) ) {
                nValue = LinearCT[i];
                if ( nCtMode & CT_MODE_ABC_NUMBERS ) {
                    len = MakeAbcNumber( szValue, (int)sizeof(szValue), (!bNext && bAddDelim)? ITEM_DELIMETER : NULL, nValue );
                } else
                if ( nCtMode & CT_MODE_NO_ORPHANS ) {

                    len = MakeDecNumber( szValue, (int)sizeof(szValue), bLessThanPrev? "-":ITEM_DELIMETER, nValue );
                } else {
                    len = MakeDecNumber( szValue, (int)sizeof(szValue), i? ITEM_DELIMETER:NULL, nValue );
                }
                if ( 0 <= len && nLen+len < nLen_szLinearCT ) {
                    if ( len ) {
                        strcpy( szLinearCT+nLen, szValue );
                        nLen += len;
                        bNext ++;
                    }
                } else {
                    bOvfl = 1;
                    break;
                }
            }
        }
    }
    *bOverflow |= bOvfl;
    return nLen;
}

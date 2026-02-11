FillIsotopicAtLinearCT(int num_atoms, sp_ATOM* at,
                           const AT_RANK *nAtomNumber,
                           AT_ISOTOPIC *LinearCTIsotopic,
                           int nMaxLenLinearCTIsotopic, int *pnLenLinearCTIsotopic)
{


    int  i, k, rank;
    int  nLinearCTIsotopicLen=0;


    if ( LinearCTIsotopic && nMaxLenLinearCTIsotopic > 0 ) {
        memset( LinearCTIsotopic, 0, nMaxLenLinearCTIsotopic * sizeof(LinearCTIsotopic[0]) );
    } else {
        return 0;
    }


    for ( rank = 1; rank <= num_atoms; rank ++ ) {

        i = (int)nAtomNumber[rank-1];


        k = ( !at[i].endpoint && !(at[i].cFlags & AT_FLAG_ISO_H_POINT) && (at[i].num_iso_H[0] || at[i].num_iso_H[1] || at[i].num_iso_H[2]) );
        if ( at[i].iso_atw_diff || k ) {
            if ( CHECK_OVERFLOW(nLinearCTIsotopicLen, nMaxLenLinearCTIsotopic) )
                return CT_OVERFLOW;
            LinearCTIsotopic[nLinearCTIsotopicLen].at_num       = (AT_RANK)rank;
            LinearCTIsotopic[nLinearCTIsotopicLen].iso_atw_diff = at[i].iso_atw_diff;
            LinearCTIsotopic[nLinearCTIsotopicLen].num_1H       = (NUM_H)(k? at[i].num_iso_H[0] : 0);
            LinearCTIsotopic[nLinearCTIsotopicLen].num_D        = (NUM_H)(k? at[i].num_iso_H[1] : 0);
            LinearCTIsotopic[nLinearCTIsotopicLen].num_T        = (NUM_H)(k? at[i].num_iso_H[2] : 0);
            nLinearCTIsotopicLen ++;
        }

    }

    if ( LinearCTIsotopic ) {
        if ( *pnLenLinearCTIsotopic ) {
            if ( *pnLenLinearCTIsotopic != nLinearCTIsotopicLen )
                return CT_LEN_MISMATCH;
        }else
            *pnLenLinearCTIsotopic = nLinearCTIsotopicLen;
    }


    return nLinearCTIsotopicLen;
}

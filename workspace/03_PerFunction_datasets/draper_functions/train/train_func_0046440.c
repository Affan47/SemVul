MarkUnusedAndEmptyLayers( char sDifSegs[][DIFS_LENGTH] )
{


    int i, nLayer, sBits, nFirstSegm;
#define nFirstFmlSegm   DIFS_f_FORMULA
#define nFirstIsoSegm   DIFS_i_IATOMS

    nLayer = DIFL_FI;
    nFirstSegm = nFirstIsoSegm;
    sBits  = 0;
    for ( i = 0; i < DIFS_idf_LENGTH; i ++ ) {
        sBits |= sDifSegs[nLayer][i];
    }
    if ( !(sBits & DIFV_OUTPUT_OMIT_F) ) {

        memset( sDifSegs[nLayer], DIFV_BOTH_EMPTY, DIFS_idf_LENGTH);
    } else
    if ( sDifSegs[nLayer][nFirstSegm] == DIFV_BOTH_EMPTY ||
         !(sDifSegs[nLayer][nFirstSegm] & DIFV_OUTPUT_OMIT_F) ) {
        sDifSegs[nLayer][nFirstSegm] = DIFV_IS_EMPTY;
    }


    nLayer = DIFL_MI;
    nFirstSegm = nFirstIsoSegm;
    sBits  = 0;
    for ( i = 0; i < DIFS_idf_LENGTH; i ++ ) {
        sBits |= sDifSegs[nLayer][i];
    }
    if ( !(sBits & DIFV_OUTPUT_OMIT_F) ) {

        memset( sDifSegs[nLayer], DIFV_BOTH_EMPTY, DIFS_idf_LENGTH);
    } else
    if ( sDifSegs[nLayer][nFirstSegm] == DIFV_BOTH_EMPTY ||
         !(sDifSegs[nLayer][nFirstSegm] & DIFV_OUTPUT_OMIT_F) ) {
        sDifSegs[nLayer][nFirstSegm] = DIFV_IS_EMPTY;
    }


    nLayer = DIFL_F;
    nFirstSegm = nFirstFmlSegm;
    sBits  = 0;
    for ( i = 0; i < DIFS_idf_LENGTH; i ++ ) {
        sBits |= sDifSegs[nLayer][i];
    }
    if ( !(sBits & DIFV_OUTPUT_OMIT_F) &&
         sDifSegs[DIFL_FI][nFirstIsoSegm] == DIFV_BOTH_EMPTY ) {

        memset( sDifSegs[nLayer], DIFV_BOTH_EMPTY, DIFS_idf_LENGTH);
    } else

    if ( sDifSegs[nLayer][nFirstSegm] == DIFV_BOTH_EMPTY ||
         !(sDifSegs[nLayer][nFirstSegm] & DIFV_OUTPUT_OMIT_F) ) {
        sDifSegs[nLayer][nFirstSegm] = DIFV_IS_EMPTY;
    }


    return 0;
#undef nFirstFmlSegm
#undef nFirstIsoSegm
}

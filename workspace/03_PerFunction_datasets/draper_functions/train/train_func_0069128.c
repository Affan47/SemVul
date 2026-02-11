CompareIcr( ICR *picr1, ICR *picr2, INCHI_MODE *pin1, INCHI_MODE *pin2, INCHI_MODE mask )
{
    int nNumExtraBits1 = 0, nNumExtraBits2 = 0, bit1, bit2;
    INCHI_MODE Flg1=picr1->flags, Flg2 = picr2->flags, cur_bit = 1, in1, in2;
    int i, ret;


    in1 = in2 = 0;
    for ( i = 0; Flg1 || Flg2; i ++, Flg1 >>= 1, Flg2 >>= 1, cur_bit <<= 1 ) {
        if ( !(mask & cur_bit) ) {
            continue;
        }
        bit1 = Flg1 & 1;
        bit2 = Flg2 & 1;
        if ( bit1 && !bit2 ) {
            in1 |= 1 << i;
            nNumExtraBits1 ++;
        } else
        if ( !bit1 && bit2 ) {
            in2 |= 1 << i;
            nNumExtraBits2 ++;
        }
    }
    if ( nNumExtraBits1 && !nNumExtraBits2 ) {
        ret = 1;
    } else
    if ( !nNumExtraBits1 && nNumExtraBits2 ) {
        ret = -1;
    } else
    if ( !in1 && !in2 ) {
        ret = 0;
    } else {
        ret = 2;
    }
    if ( pin1 ) *pin1 = in1;
    if ( pin2 ) *pin2 = in2;

    return ret;
}

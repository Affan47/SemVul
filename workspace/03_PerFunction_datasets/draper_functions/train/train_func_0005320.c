IsEqInfoCVars (
    Bag                 dst,
    Bag                 src )
{
    Int                 i;
    if ( SIZE_BAG(dst) < SIZE_BAG(src) )  ResizeBag( dst, SIZE_BAG(src) );
    if ( SIZE_BAG(src) < SIZE_BAG(dst) )  ResizeBag( src, SIZE_BAG(dst) );
    for ( i = 1; i <= NLVAR_INFO(src); i++ ) {
        if ( TNUM_LVAR_INFO(dst,i) != TNUM_LVAR_INFO(src,i) ) {
            return 0;
        }
    }
    for ( i = 1; i <= NTEMP_INFO(dst) && i <= NTEMP_INFO(src); i++ ) {
        if ( TNUM_TEMP_INFO(dst,i) != TNUM_TEMP_INFO(src,i) ) {
            return 0;
        }
    }
    return 1;
}

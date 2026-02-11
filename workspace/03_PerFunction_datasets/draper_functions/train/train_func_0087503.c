EqBlist (
    Obj                 listL,
    Obj                 listR )
{
    long                lenL;
    long                lenR;
    UInt *              ptrL;
    UInt *              ptrR;
    UInt                i;


    lenL = LEN_BLIST( listL );
    lenR = LEN_BLIST( listR );
    if ( lenL != lenR ) {
        return 0L;
    }


    ptrL = BLOCKS_BLIST(listL);
    ptrR = BLOCKS_BLIST(listR);
    for ( i = (lenL+BIPEB-1)/BIPEB; 0 < i; i-- ) {
        if ( *ptrL++ != *ptrR++ )
            return 0L;
    }


    return 1L;
}

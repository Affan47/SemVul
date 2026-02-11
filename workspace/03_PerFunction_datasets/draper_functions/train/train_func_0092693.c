EqPerm44 (
    Obj                 opL,
    Obj                 opR )
{
    UInt                degL;
    UInt4 *             ptL;
    UInt                degR;
    UInt4 *             ptR;
    UInt                p;


    degL = DEG_PERM4(opL);
    degR = DEG_PERM4(opR);


    ptL = ADDR_PERM4(opL);
    ptR = ADDR_PERM4(opR);


    if ( degL <= degR ) {
        for ( p = 0; p < degL; p++ )
            if ( *(ptL++) != *(ptR++) )
                return 0L;
        for ( p = degL; p < degR; p++ )
            if (        p != *(ptR++) )
                return 0L;
    }
    else {
        for ( p = 0; p < degR; p++ )
            if ( *(ptL++) != *(ptR++) )
                return 0L;
        for ( p = degR; p < degL; p++ )
            if ( *(ptL++) !=        p )
                return 0L;
    }


    return 1L;
}

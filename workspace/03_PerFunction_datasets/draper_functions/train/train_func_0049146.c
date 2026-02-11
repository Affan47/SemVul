PowPerm22 (
    Obj                 opL,
    Obj                 opR )
{
    Obj                 cnj;
    UInt                degC;
    UInt2 *             ptC;
    UInt                degL;
    UInt2 *             ptL;
    UInt                degR;
    UInt2 *             ptR;
    UInt                p;


    degL = DEG_PERM2(opL);
    degR = DEG_PERM2(opR);
    degC = degL < degR ? degR : degL;
    cnj = NEW_PERM2( degC );


    ptL = ADDR_PERM2(opL);
    ptR = ADDR_PERM2(opR);
    ptC = ADDR_PERM2(cnj);


    if ( degL == degR ) {
        for ( p = 0; p < degC; p++ )
            ptC[ ptR[p] ] = ptR[ ptL[p] ];
    }


    else {
        for ( p = 0; p < degC; p++ )
            ptC[ IMAGE(p,ptR,degR) ] = IMAGE( IMAGE(p,ptL,degL), ptR, degR );
    }


    return cnj;
}

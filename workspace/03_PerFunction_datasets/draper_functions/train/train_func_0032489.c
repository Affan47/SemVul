SumIntVector (
    Obj                 elmL,
    Obj                 vecR )
{
    Obj                 vecS;
    Obj *               ptrS;
    Obj                 elmS;
    Obj *               ptrR;
    Obj                 elmR;
    UInt                len;
    UInt                i;


    len = LEN_PLIST( vecR );
    vecS = NEW_PLIST( TNUM_OBJ(vecR), len );
    SET_LEN_PLIST( vecS, len );


    ptrR = ADDR_OBJ( vecR );
    ptrS = ADDR_OBJ( vecS );
    for ( i = 1; i <= len; i++ ) {
        elmR = ptrR[i];
        if ( ! ARE_INTOBJS(elmL,elmR) || ! SUM_INTOBJS(elmS,elmL,elmR) ) {
            CHANGED_BAG( vecS );
            elmS = SUM( elmL, elmR );
            ptrR = ADDR_OBJ( vecR );
            ptrS = ADDR_OBJ( vecS );
        }
        ptrS[i] = elmS;
    }


    CHANGED_BAG( vecS );
    return vecS;
}

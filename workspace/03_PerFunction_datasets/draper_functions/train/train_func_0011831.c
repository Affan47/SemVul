ProdVectorInt (
    Obj                 vecL,
    Obj                 elmR )
{
    Obj                 vecP;
    Obj *               ptrP;
    Obj                 elmP;
    Obj *               ptrL;
    Obj                 elmL;
    UInt                len;
    UInt                i;


    len = LEN_PLIST( vecL );
    vecP = NEW_PLIST( IS_MUTABLE_OBJ(vecL) ?
                      T_PLIST_CYC :T_PLIST_CYC+IMMUTABLE, len );
    SET_LEN_PLIST( vecP, len );


    ptrL = ADDR_OBJ( vecL );
    ptrP = ADDR_OBJ( vecP );
    for ( i = 1; i <= len; i++ ) {
        elmL = ptrL[i];
        if ( ! ARE_INTOBJS(elmL,elmR) || ! PROD_INTOBJS(elmP,elmL,elmR) ) {
            CHANGED_BAG( vecP );
            elmP = PROD( elmL, elmR );
            ptrL = ADDR_OBJ( vecL );
            ptrP = ADDR_OBJ( vecP );
        }
        ptrP[i] = elmP;
    }


    CHANGED_BAG( vecP );
    return vecP;
}

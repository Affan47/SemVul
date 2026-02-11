ProdVecFFEFFE (
    Obj                 vecL,
    Obj                 elmR )
{
    Obj                 vecP;
    Obj *               ptrP;
    FFV                 valP;
    Obj *               ptrL;
    FFV                 valL;
    UInt                len;
    UInt                i;
    FF                  fld;
    FF *                succ;
    FFV                 valR;


    fld = FLD_FFE( ELM_PLIST( vecL, 1 ) );
    if( FLD_FFE( elmR ) != fld ) {

        if( CHAR_FF( fld ) == CHAR_FF( FLD_FFE( elmR ) ) )
            return ProdListScl( vecL, elmR );

        elmR = ErrorReturnObj(
         "<vec>*<elm>: <elm> and <vec> must belong to the same finite field",
         0L, 0L, "you can replace <elm> via 'return <elm>;'" );
        return PROD( vecL, elmR );
    }


    len = LEN_PLIST( vecL );
    vecP = NEW_PLIST( IS_MUTABLE_OBJ(vecL) ?
		      T_PLIST_FFE :T_PLIST_FFE+IMMUTABLE, len );
    SET_LEN_PLIST( vecP, len );


    succ = SUCC_FF( fld );


    valR = VAL_FFE( elmR );
    ptrL = ADDR_OBJ( vecL );
    ptrP = ADDR_OBJ( vecP );
    for ( i = 1; i <= len; i++ ) {
        valL = VAL_FFE( ptrL[i] );
        valP = PROD_FFV( valL, valR, succ );
        ptrP[i] = NEW_FFE( fld, valP );
    }


    return vecP;
}

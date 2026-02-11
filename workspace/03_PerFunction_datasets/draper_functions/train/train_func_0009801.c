SumVectorVector (
    Obj                 vecL,
    Obj                 vecR )
{
    Obj                 vecS;
    Obj *               ptrS;
    Obj                 elmS;
    Obj *               ptrL;
    Obj                 elmL;
    Obj *               ptrR;
    Obj                 elmR;
    UInt                lenL, lenR, len, lenmin;
    UInt                i;


    lenL = LEN_PLIST( vecL );
    lenR = LEN_PLIST( vecR );
    if (lenL < lenR)
      {
        lenmin = lenL;
        len = lenR;
      } else {
        lenmin = lenR;
        len = lenL;
      }
    vecS = NEW_PLIST( (IS_IMM_PLIST(vecL) && IS_IMM_PLIST(vecR)) ?
                      T_PLIST_CYC+IMMUTABLE : T_PLIST_CYC, len );
    SET_LEN_PLIST( vecS, len );


    ptrL = ADDR_OBJ( vecL );
    ptrR = ADDR_OBJ( vecR );
    ptrS = ADDR_OBJ( vecS );
    for ( i = 1; i <= lenmin; i++ ) {
        elmL = ptrL[i];
        elmR = ptrR[i];
        if ( ! ARE_INTOBJS(elmL,elmR) || ! SUM_INTOBJS(elmS,elmL,elmR) ) {
            CHANGED_BAG( vecS );
            elmS = SUM( elmL, elmR );
            ptrL = ADDR_OBJ( vecL );
            ptrR = ADDR_OBJ( vecR );
            ptrS = ADDR_OBJ( vecS );
        }
        ptrS[i] = elmS;
    }
    if (lenL < lenR)
      for (;i <= lenR; i++) {
        ptrS[i] = ptrR[i];
      }
    else
      for (;i <= lenL; i++) {
        ptrS[i] = ptrL[i];
      }

    CHANGED_BAG( vecS );
    return vecS;
}

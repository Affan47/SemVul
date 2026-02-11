PosPlistHomSort (
    Obj                 list,
    Obj                 val,
    Obj                 start )
{
    UInt                lenList;
    UInt                i, j, k;
    UInt                istart;


    if (!IS_INTOBJ(start))
      return Fail;

    istart = INT_INTOBJ(start);


    if (FAMILY_OBJ(val) != FAMILY_OBJ(ELM_PLIST(list,1)))
      return Fail;


    lenList = LEN_PLIST( list );


    i = istart;  k = lenList + 1;
    while ( i+1 < k ) {
        j = (i + k) / 2;
        if ( LT( ELM_PLIST(list,j), val ) )  i = j;
        else                                 k = j;
    }


    if ( lenList < k || ! EQ( ELM_PLIST(list,k), val ) )
        k = 0;


    return k == 0 ? Fail: INTOBJ_INT(k);
}

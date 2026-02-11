FuncSUB_FLAGS (
    Obj                 self,
    Obj                 flags1,
    Obj                 flags2 )
{
    Obj                 flags;
    Int                 len1;
    Int                 len2;
    Int                 size1;
    Int                 size2;
    UInt *              ptr;
    UInt *              ptr1;
    UInt *              ptr2;
    Int                 i;


    while ( TNUM_OBJ(flags1) != T_FLAGS ) {
        flags1 = ErrorReturnObj( "<flags1> must be a flags list (not a %s)",
            (Int)TNAM_OBJ(flags1), 0L,
            "you can replace <flags1> via 'return <flags1>;'" );
    }
    while ( TNUM_OBJ(flags2) != T_FLAGS ) {
        flags2 = ErrorReturnObj( "<flags2> must be a flags list (not a %s)",
            (Int)TNAM_OBJ(flags2), 0L,
            "you can replace <flags2> via 'return <flags2>;'" );
    }


    len1   = LEN_FLAGS(flags1);
    size1  = NRB_FLAGS(flags1);
    len2   = LEN_FLAGS(flags2);
    size2  = NRB_FLAGS(flags2);
    if ( len1 < len2 ) {
        NEW_FLAGS( flags, len1 );
        SET_LEN_FLAGS( flags, len1 );
        ptr1 = BLOCKS_FLAGS(flags1);
        ptr2 = BLOCKS_FLAGS(flags2);
        ptr  = BLOCKS_FLAGS(flags);
        for ( i = 1; i <= size1; i++ )
            *ptr++ = *ptr1++ & ~ *ptr2++;
    }
    else {
        NEW_FLAGS( flags, len1 );
        SET_LEN_FLAGS( flags, len1 );
        ptr1 = BLOCKS_FLAGS(flags1);
        ptr2 = BLOCKS_FLAGS(flags2);
        ptr  = BLOCKS_FLAGS(flags);
        for ( i = 1; i <= size2; i++ )
            *ptr++ = *ptr1++ & ~ *ptr2++;
        for (      ; i <= size1; i++ )
            *ptr++ = *ptr1++;
    }

    return flags;
}

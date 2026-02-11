FuncLEN_FLAGS (
    Obj                 self,
    Obj                 flags )
{

    while ( TNUM_OBJ(flags) != T_FLAGS ) {
        flags = ErrorReturnObj( "<flags> must be a flags list (not a %s)",
            (Int)TNAM_OBJ(flags), 0L,
            "you can replace <flags> via 'return <flags>;'" );
    }

    return INTOBJ_INT( LEN_FLAGS(flags) );
}

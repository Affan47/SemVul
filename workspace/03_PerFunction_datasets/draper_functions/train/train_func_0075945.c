FuncShrinkAllocationPlist( Obj self, Obj plist )
{
    while ( ! IS_PLIST(plist) ) {
        plist = ErrorReturnObj(
            "<plist> must be a plain list (not a %s)",
            (Int)TNAM_OBJ(plist), 0,
            "you can replace <plist> via 'return <plist>;'" );
    }
    SHRINK_PLIST(plist, LEN_PLIST(plist));
    return (Obj)0;
}

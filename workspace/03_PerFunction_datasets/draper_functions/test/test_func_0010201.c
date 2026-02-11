FuncOUTPUT_TEXT_FILE (
    Obj             self,
    Obj             filename,
    Obj             append )
{
    Int             fid;


    while ( ! IsStringConv( filename ) ) {
        filename = ErrorReturnObj(
            "<filename> must be a string (not a %s)",
            (Int)TNAM_OBJ(filename), 0L,
            "you can replace <filename> via 'return <filename>;'" );
    }
    while ( append != True && append != False ) {
        filename = ErrorReturnObj(
            "<append> must be a boolean (not a %s)",
            (Int)TNAM_OBJ(append), 0L,
            "you can replace <append> via 'return <append>;'" );
    }


    SyClearErrorNo();
    if ( append == True ) {
        fid = SyFopen( CSTR_STRING(filename), "a" );
    }
    else {
        fid = SyFopen( CSTR_STRING(filename), "w" );
    }
    if ( fid == - 1)
        SySetErrorNo();
    return fid == -1 ? Fail : INTOBJ_INT(fid);
}

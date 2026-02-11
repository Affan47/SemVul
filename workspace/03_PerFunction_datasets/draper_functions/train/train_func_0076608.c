FuncUNB_GVAR (
    Obj                 self,
    Obj                 gvar )
{

    while ( ! IsStringConv( gvar ) ) {
        gvar = ErrorReturnObj(
            "UNB_GVAR: <gvar> must be a string (not a %s)",
            (Int)TNAM_OBJ(gvar), 0L,
            "you can return a string for <gvar>" );
    }


    AssGVar( GVarName( CSTR_STRING(gvar) ), (Obj)0 );
    return (Obj) 0;
}

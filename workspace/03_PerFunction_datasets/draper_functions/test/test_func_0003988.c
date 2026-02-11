FuncVAL_GVAR (
    Obj                 self,
   Obj                 gvar )
{
  Obj val;

    while ( ! IsStringConv( gvar ) ) {
        gvar = ErrorReturnObj(
            "VAL_GVAR: <gvar> must be a string (not a %s)",
            (Int)TNAM_OBJ(gvar), 0L,
            "you can return a string for <gvar>" );
    }


    val = ValAutoGVar( GVarName( CSTR_STRING(gvar) ) );

    while (val == (Obj) 0)
      val = ErrorReturnObj("VAL_GVAR: No value bound to %s",
                           (Int)CSTR_STRING(gvar), (Int) 0,
                           "you can return a value" );
    return val;
}

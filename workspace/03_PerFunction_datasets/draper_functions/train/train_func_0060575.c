CompUnknownBool (
    Expr                expr )
{
    CVar                res;
    CVar                val;


    res = CVAR_TEMP( NewTemp( "res" ) );


    val = CompExpr( expr );
    CompCheckBool( val );


    Emit( "%c = (Obj)(UInt)(%c != False);\n", res, val );


    SetInfoCVar( res, W_BOOL );


    if ( IS_TEMP_CVAR( val ) )  FreeTemp( TEMP_CVAR( val ) );


    return res;
}

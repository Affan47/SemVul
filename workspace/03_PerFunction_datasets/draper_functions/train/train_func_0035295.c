CompRangeExpr (
    Expr                expr )
{
    CVar                range;
    CVar                first;
    CVar                second;
    CVar                last;


    range = CVAR_TEMP( NewTemp( "range" ) );


    if ( SIZE_EXPR(expr) == 2 * sizeof(Expr) ) {
        first  = CompExpr( ADDR_EXPR(expr)[0] );
        second = 0;
        last   = CompExpr( ADDR_EXPR(expr)[1] );
    }
    else {
        first  = CompExpr( ADDR_EXPR(expr)[0] );
        second = CompExpr( ADDR_EXPR(expr)[1] );
        last   = CompExpr( ADDR_EXPR(expr)[2] );
    }


    if ( SIZE_EXPR(expr) == 2 * sizeof(Expr) ) {
        Emit( "%c = Range2Check( %c, %c );\n",
              range, first, last );
    }
    else {
        Emit( "%c = Range3Check( %c, %c, %c );\n",
              range, first, second, last );
    }


    SetInfoCVar( range, W_LIST );


    if ( SIZE_EXPR(expr) == 2 * sizeof(Expr) ) {
        if ( IS_TEMP_CVAR( last   ) )  FreeTemp( TEMP_CVAR( last   ) );
        if ( IS_TEMP_CVAR( first  ) )  FreeTemp( TEMP_CVAR( first  ) );
    }
    else {
        if ( IS_TEMP_CVAR( last   ) )  FreeTemp( TEMP_CVAR( last   ) );
        if ( IS_TEMP_CVAR( second ) )  FreeTemp( TEMP_CVAR( second ) );
        if ( IS_TEMP_CVAR( first  ) )  FreeTemp( TEMP_CVAR( first  ) );
    }


    return range;
}

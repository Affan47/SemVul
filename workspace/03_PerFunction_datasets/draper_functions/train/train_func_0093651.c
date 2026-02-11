CompIf (
    Stat                stat )
{
    CVar                cond;
    UInt                nr;
    Bag                 info_in;
    Bag                 info_out;
    UInt                i;


    nr = SIZE_STAT( stat ) / (2*sizeof(Stat));


    if ( CompPass == 2 ) {
        Emit( "\n/* if " );
        PrintExpr( ADDR_STAT(stat)[0] );
        Emit( " then */\n" );
    }


    cond = CompBoolExpr( ADDR_STAT( stat )[0] );


    Emit( "if ( %c ) {\n", cond );
    if ( IS_TEMP_CVAR( cond ) )  FreeTemp( TEMP_CVAR( cond ) );


    info_in = NewInfoCVars();
    CopyInfoCVars( info_in, INFO_FEXP(CURR_FUNC) );


    CompStat( ADDR_STAT( stat )[1] );


    info_out = NewInfoCVars();
    CopyInfoCVars( info_out, INFO_FEXP(CURR_FUNC) );


    Emit( "\n}\n" );


    for ( i = 2; i <= nr; i++ ) {


        if ( i == nr && TNUM_EXPR(ADDR_STAT(stat)[2*(i-1)]) == T_TRUE_EXPR )
            break;


        if ( CompPass == 2 ) {
            Emit( "\n/* elif " );
            PrintExpr( ADDR_STAT(stat)[2*(i-1)] );
            Emit( " then */\n" );
        }


        Emit( "else {\n" );


        CopyInfoCVars( INFO_FEXP(CURR_FUNC), info_in );


        cond = CompBoolExpr( ADDR_STAT( stat )[2*(i-1)] );


        Emit( "if ( %c ) {\n", cond );
        if ( IS_TEMP_CVAR( cond ) )  FreeTemp( TEMP_CVAR( cond ) );


        CopyInfoCVars( info_in, INFO_FEXP(CURR_FUNC) );


        CompStat( ADDR_STAT( stat )[2*(i-1)+1] );


        MergeInfoCVars( info_out, INFO_FEXP(CURR_FUNC) );


        Emit( "\n}\n" );

    }


    if ( i == nr ) {


        if ( CompPass == 2 ) {
            Emit( "\n/* else */\n" );
        }


        Emit( "else {\n" );


        CopyInfoCVars( INFO_FEXP(CURR_FUNC), info_in );


        CompStat( ADDR_STAT( stat )[2*(i-1)+1] );


        MergeInfoCVars( info_out, INFO_FEXP(CURR_FUNC) );


        Emit( "\n}\n" );

    }


    else {


        CopyInfoCVars( INFO_FEXP(CURR_FUNC), info_in );


        MergeInfoCVars( info_out, INFO_FEXP(CURR_FUNC) );

    }


    for ( i = 2; i <= nr; i++ ) {
        if ( i == nr && TNUM_EXPR(ADDR_STAT(stat)[2*(i-1)]) == T_TRUE_EXPR )
            break;
        Emit( "}\n" );
    }
    Emit( "/* fi */\n" );


    CopyInfoCVars( INFO_FEXP(CURR_FUNC), info_out );

}

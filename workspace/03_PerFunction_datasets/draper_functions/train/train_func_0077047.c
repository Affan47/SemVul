GetInfoCVar (
    CVar                cvar )
{
    Bag                 info;


    info = INFO_FEXP( CURR_FUNC );


    if ( IS_INTG_CVAR(cvar) ) {
        return ((0 < INTG_CVAR(cvar)) ? W_INT_SMALL_POS : W_INT_SMALL);
    }


    else if ( IS_TEMP_CVAR(cvar) ) {
        return TNUM_TEMP_INFO( info, TEMP_CVAR(cvar) );
    }


    else if ( IS_LVAR_CVAR(cvar) ) {
        return TNUM_LVAR_INFO( info, LVAR_CVAR(cvar) );
    }


    else {
        return 0;
    }
}

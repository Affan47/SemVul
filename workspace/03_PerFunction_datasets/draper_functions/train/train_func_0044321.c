make1d( state * pState )
{
    TARGET * t      = pState->t;
    CMD    * cmd    = (CMD *)t->cmds;
    int      status = pState->status;

    if ( t->flags & T_FLAG_FAIL_EXPECTED && !globs.noexec )
    {

        switch ( status )
        {
            case EXEC_CMD_FAIL: status = EXEC_CMD_OK  ; break;
            case EXEC_CMD_OK:   status = EXEC_CMD_FAIL; break;
        }
    }

    if ( ( status == EXEC_CMD_FAIL ) &&
         ( cmd->rule->actions->flags & RULE_IGNORE ) )
        status = EXEC_CMD_OK;


    if ( status == EXEC_CMD_INTR )
        ++intr;


    if ( ( status == EXEC_CMD_FAIL ) && DEBUG_MAKE )
    {
        if ( !DEBUG_EXEC )
            printf( "%s\n", cmd->buf->value );

        printf( "...failed %s ", object_str( cmd->rule->name ) );
        list_print( lol_get( &cmd->args, 0 ) );
        printf( "...\n" );
    }


    if ( ( status == EXEC_CMD_FAIL ) && globs.quitquick )
        ++intr;


    if (status != EXEC_CMD_OK)
    {
        LIST * targets = lol_get( &cmd->args, 0 );
        LISTITER iter = list_begin( targets ), end = list_end( targets );
        for ( ; iter != end; iter = list_next( iter ) )
        {
            int need_unlink = 1;
            TARGET* t = bindtarget ( list_item( iter ) );
            if (t->flags & T_FLAG_PRECIOUS)
            {
                need_unlink = 0;
            }
            if (need_unlink && !unlink( object_str( list_item( iter ) ) ) )
                printf( "...removing %s\n", object_str( list_item( iter ) ) );
        }
    }


    t->status = status;
    t->cmds = (char *)cmd_next( cmd );
    cmd_free( cmd );
    pState->curstate = T_STATE_MAKE1C;
}

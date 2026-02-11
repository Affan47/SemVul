fli_handle_event_callbacks( XEvent * xev )
{
    Window win = ( ( XAnyEvent * ) xev )->window;
    FLI_WIN *fwin = fli_app_win;

    while ( fwin && fwin->win != win )
        fwin = fwin->next;

    if ( ! fwin )
    {


        if ( fli_event_callback && ! fli_event_callback( xev, fli_user_data ) )
            return 1;

        M_warn( "fli_handle_event_callbacks", "Unknown window = %ld",
                xev->xany.window );
        fli_xevent_name( "Ignored", xev );
        return 1;
    }

    if (    fwin->pre_emptive
         && fwin->pre_emptive( xev, fwin->pre_emptive_data ) == FL_PREEMPT )
        return 1;

    if ( fwin->callback[ xev->type ] )
    {
        fwin->callback[ xev->type ]( xev, fwin->user_data[ xev->type ] );
        return 1;
    }

    return 0;
}

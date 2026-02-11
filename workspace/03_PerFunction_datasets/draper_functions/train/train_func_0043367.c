check_for_activity( PIDList * cur )
{
    XEvent xev;


    do
    {
        if ( fl_check_forms( ) == FL_EVENT )
            fl_XNextEvent( &xev );
    } while (    fli_is_watched_io( cur->fd_out )
              || fli_is_watched_io( cur->fd_err ) );

    fl_update_display( 1 );
}

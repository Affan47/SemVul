fli_choice_cleanup( void )
{
    if ( ! fd_choice )
        return;

    if ( fd_choice->sc[ 0 ] )
        fl_free( ( char * ) fd_choice->sc[ 0 ] );

    if ( fd_choice->sc[ 1 ] )
        fl_free( ( char * ) fd_choice->sc[ 1 ] );

    if ( fd_choice->sc[ 2 ] )
        fl_free( ( char * ) fd_choice->sc[ 2 ] );

    fl_safe_free( fd_choice );
}

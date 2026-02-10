fl_winshow( Window win )
{
    XMapRaised( flx->display, win );


    if ( st_xwmh.initial_state == NormalState )
        wait_mapwin( win );

    setup_catch_destroy( win );
    fl_winset( win );


    fli_default_xswa( );
    return win;
}

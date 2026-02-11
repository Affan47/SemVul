handle_expose( XEvent * xev,
               void   * p  FL_UNUSED_ARG )
{
    if ( xev->xexpose.count == 0 )
    {
        M_warn( "FD_Expose", "" );


        if ( ignored_fake_configure )
            fl_get_winsize( main_window, &winw, &winh );


        if ( cur_form && ( cur_form->w != winw || cur_form->h != winh ) )
            reshape_form_background( winw, winh );

        redraw_the_form( 1 );
        ignored_fake_configure = 0;
        return 1;
    }

    return 0;
}

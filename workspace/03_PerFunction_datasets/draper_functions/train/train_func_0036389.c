handle_ConfigureNotify_event( FL_FORM  * evform,
                              FL_FORM ** redraw_form )
{
    Window win = st_xev.xany.window;
    int old_w = evform->w;
    int old_h = evform->h;

    if ( ! evform )
        return;

    if ( ! st_xev.xconfigure.send_event )
        fl_get_winorigin( win, &evform->x, &evform->y );
    else
    {
        evform->x = st_xev.xconfigure.x;
        evform->y = st_xev.xconfigure.y;
        M_warn( "handle_ConfigureNotify_event", "WMConfigure:x = %d y = %d"
                "w = %d h = %d", evform->x, evform->y, st_xev.xconfigure.width,
                st_xev.xconfigure.height );
    }


    ignored_fake_configure =    st_xev.xconfigure.send_event
                             && (    st_xev.xconfigure.width  != evform->w
                                  || st_xev.xconfigure.height != evform->h );


    fli_handle_form( evform, FL_MOVEORIGIN, 0, &st_xev );

    if ( st_xev.xconfigure.send_event )
        return;


    fli_scale_form( evform, ( double ) st_xev.xconfigure.width  / evform->w,
                    ( double ) st_xev.xconfigure.height / evform->h );


    if ( evform->w <= old_w && evform->h <= old_h )
        fl_redraw_form( evform );
    else if ( ! ( evform->w > old_w && evform->h > old_h ) )
        *redraw_form = evform;
}

fli_handle_idling( XEvent * xev,
                   long     msec,
                   int      do_idle_cb )
{
    int i;


    fli_watch_io( fli_context->io_rec, msec );


    if ( fli_handle_signal )
        fli_handle_signal( );


    if ( fli_int.query_age > 0 && fli_int.mouseform )
    {
        fl_get_form_mouse( fli_int.mouseform, &fli_int.mousex, &fli_int.mousey,
                           &fli_int.keymask );
        fli_int.query_age = 0;
        xev->xmotion.time = CurrentTime;
    }
    else
        xev->xmotion.time += msec;


    xev->type            = MotionNotify;
    xev->xany.window     = fli_int.mouseform ? fli_int.mouseform->window : None;
    xev->xany.send_event = 1;
    xev->xmotion.state   = fli_int.keymask;
    xev->xmotion.x       = fli_int.mousex;
    xev->xmotion.y       = fli_int.mousey;
    xev->xmotion.is_hint = 0;


    if (    button_down( fli_int.keymask )
         && fli_int.pushobj
         && fli_int.pushobj->want_update
         && fli_int.mouseform )
        fli_handle_form( fli_int.mouseform, FL_UPDATE,
                         xmask2button( fli_int.keymask ), xev );


    if ( fli_int.auto_count )
        for ( i = 0; i < fli_int.formnumb; i++ )
            if ( fli_int.forms[ i ]->num_auto_objects )
                fli_handle_form( fli_int.forms[ i ], FL_STEP, 0, xev );


    if (    do_idle_cb
         && fli_context->idle_rec
         && fli_context->idle_rec->callback )
        fli_context->idle_rec->callback( xev, fli_context->idle_rec->data );
}

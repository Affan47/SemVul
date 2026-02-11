popup_interaction( FL_POPUP * popup )
{
    FL_POPUP *p;
    FL_POPUP_ENTRY *e = NULL;
    XEvent ev;
    int timer_cnt = 0;

    ev.xmotion.time = 0;

    while ( 1 )
    {
        long msec = fli_context->idle_delta;

        if ( fli_context->timeout_rec )
            fli_handle_timeouts( &msec );


        if ( ! XCheckWindowEvent( flx->display, popup->win, popup->event_mask,
                                  &ev ) )
        {
            if ( timer_cnt++ % 10 == 0 )
            {
                timer_cnt = 0;
                fli_handle_idling( &ev, msec, 1 );
                fl_winset( popup->win );
            }

            continue;
        }

        timer_cnt = 0;
        fli_int.query_age++;

        switch ( ev.type )
        {
            case Expose :
                draw_popup( popup );
                break;

            case MotionNotify :
                fli_int.mousex    = ev.xmotion.x;
                fli_int.mousey    = ev.xmotion.y;
                fli_int.keymask   = ev.xmotion.state;
                fli_int.query_age = 0;

                fli_compress_event( &ev, PointerMotionMask );
                popup = handle_motion( popup, ev.xmotion.x, ev.xmotion.y );
                break;

            case ButtonRelease :
            case ButtonPress :
                fli_int.mousex    = ev.xbutton.x;
                fli_int.mousey    = ev.xbutton.y;
                fli_int.keymask   = ev.xbutton.state;
                fli_int.query_age = 0;


                if (    ev.xbutton.button == Button4
                     || ev.xbutton.button == Button5 )
                    break;


                e = find_entry( popup, ev.xmotion.x, ev.xmotion.y );


                if (    popup->top_parent->policy == FL_POPUP_NORMAL_SELECT
                     && ev.type == ButtonRelease
                     && ( e == NULL || e->state & FL_POPUP_DISABLED ) )
                    break;

                if (    ev.type == ButtonPress
                     && is_on_popups( popup, ev.xmotion.x, ev.xmotion.y ) )
                    break;


                for ( p = popup; p != NULL; p = p->parent )
                    close_popup( p, e == NULL );

                return handle_selection( e );

            case KeyPress :
                fli_int.mousex    = ev.xkey.x;
                fli_int.mousey    = ev.xkey.y;
                fli_int.keymask   = ev.xkey.state;
                fli_int.query_age = 0;

                if ( ( p = handle_key( popup, ( XKeyEvent * ) &ev, &e ) ) )
                    popup = p;
                else
                    return handle_selection( e );
        }
    }

    return NULL;
}

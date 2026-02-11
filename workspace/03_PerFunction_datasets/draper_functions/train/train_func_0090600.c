EventManager_init() {
    check( !em, "Event Manager already created!\n" );

    em = byte_alloc( sizeof( EventManager ) );
    check_mem( em );


    memset( em->curr_state.keyboard, false, 330 * sizeof( bool ) );
    memset( em->curr_state.mouse, false, 5 * sizeof( bool ) );
    em->curr_state.wheel = 0;
    em->curr_state.close_signal = false;

    memset( em->prev_state.keyboard, false, 330 * sizeof( bool ) );
    memset( em->prev_state.mouse, false, 5 * sizeof( bool ) );
    em->prev_state.wheel = 0;
    em->prev_state.close_signal = false;


    ListenerArray_init( &em->key_listeners, 10 );
    ListenerArray_init( &em->mouse_listeners, 10 );
    ListenerArray_init( &em->resize_listeners, 5 );

    EventArray_init( &em->frame_key_events, 50 );
    EventArray_init( &em->frame_mouse_events, 50 );
    EventArray_init( &em->frame_resize_events, 50 );


    log_info( "Event manager successfully initialized!\n" );

    return true;

error:
    EventManager_destroy();
    return false;
}

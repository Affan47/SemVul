wasp_make_os_connection( int handle, int connected ){


    wasp_os_connection oscon = WASP_OBJALLOC( os_connection );
    wasp_os_input osin = WASP_OBJALLOC( os_input );
    wasp_os_output osout = WASP_OBJALLOC( os_output );

    osin->conn = oscon;
    ((wasp_input)osin)->recv = (wasp_input_mt)wasp_os_recv_mt;
    ((wasp_output)osout)->xmit = (wasp_output_mt)wasp_os_xmit_mt;

    osout->conn = oscon;

    wasp_init_connection( (wasp_connection) oscon,
                          (wasp_input) osin,
                          (wasp_output) osout );

    oscon->handle = handle;
    oscon->event = bufferevent_new( handle,
                                    (evbuffercb) wasp_os_read_cb,
                                    (evbuffercb) wasp_os_xmit_cb,
                                    (everrorcb) wasp_os_error_cb,
                                    oscon);

    if( connected ){
        oscon->state = WASP_CONNECTED;
    }else{
        bufferevent_enable( oscon->event, EV_WRITE );
        oscon->state = WASP_CONNECTING;
        wasp_enable_conn_loop( oscon );
    }

    return oscon;
}

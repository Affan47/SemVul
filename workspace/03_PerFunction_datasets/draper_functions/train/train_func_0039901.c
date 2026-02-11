set_state( int newstate )
{
	if ( client_state == newstate ) return;

	if ( newstate == CS_PLAY )
		grab_input( 1 );
	if ( client_state == CS_PLAY )
		grab_input( 0 );
	if ( client_state == CS_CONFIRM_WARP ||
	     client_state == CS_CONFIRM_RESTART ||
	     client_state == CS_CONFIRM_QUIT ||
             client_state == CS_CONFIRM_CONTINUE ||
	     client_state == CS_GET_READY ||
	     client_state == CS_PAUSE ||
	     client_state == CS_FINAL_PLAYER_INFO ||
         client_state == CS_GET_READY_FOR_NEXT_LEVEL ||
	     client_state == CS_RECV_LEVEL ||
	     client_state == CS_ROUND_RESULT ||
	     client_state == CS_RECV_STATS ||
	     client_state == CS_FATAL_ERROR ) {

		if ( offscreen ) {
			stk_surface_blit( offscreen, 0,0,-1,-1, stk_display, 0,0 );
			end_frame();
		}


		if ( client_state != CS_RECV_LEVEL )
		if ( client_state != CS_ROUND_RESULT )
		if ( client_state != CS_RECV_STATS );
			stk_display_update( STK_UPDATE_ALL );
	}

	client_state = newstate;
	stk_timer_reset();
}

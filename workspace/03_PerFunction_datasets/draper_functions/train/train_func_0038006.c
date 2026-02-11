game_busy_callback( void (*callback)(int count), int delta_step )
{
	if ( !callback ) {


		cf_in_callback++;
		(*cf_callback)(-1);
		cf_in_callback--;

		cf_timestamp = -1;
		cf_callback = NULL;
	} else {
		cb_counter = 0;
		cb_last_counter = 0;
		cb_delta_step = delta_step;
		cf_timestamp = timer_get_milliseconds()+(1000/10);
		cf_callback = callback;


		cf_in_callback++;
		(*cf_callback)(0);
		cf_in_callback--;

	}

	return cb_counter;
}

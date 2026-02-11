game_busy(char *filename)
{
	if ( cf_in_callback != 0 ) return;
	if ( cf_timestamp < 0 ) return;
	if ( !cf_callback ) return;

	cb_counter++;


#ifndef NDEBUG
	if (filename != NULL)
		strncpy(Processing_filename, filename, MAX_PATH_LEN);
#endif

	int t1 = timer_get_milliseconds();

	if ( (t1 > cf_timestamp) || ((cb_counter > cb_last_counter+155) && (cb_delta_step > 0)) )	{
		cb_last_counter = cb_counter;
		cf_in_callback++;
		(*cf_callback)(cb_counter);
		cf_in_callback--;
		cf_timestamp = t1 + (1000/10);
	}
}

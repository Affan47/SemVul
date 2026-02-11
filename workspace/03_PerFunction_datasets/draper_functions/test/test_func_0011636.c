timing_event_pct(char *event_name)
{
#ifndef USE_TIMING
	return 0.0f;
#else
	int event;


	if(event_name == NULL){
		return -1.0f;
	}


	event = timing_event_lookup(event_name);
	if(event == -1){
		return -1.0f;
	}

	return (float)((double)Timing_events[event].microseconds_total / (double)Timing_frame.microseconds_total);
#endif
}

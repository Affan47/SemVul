timing_event_start(char *event_name)
{
#ifndef USE_TIMING
	return;
#else
	int event;


	if(event_name == NULL){
		return;
	}


	event = timing_event_lookup(event_name);


	if(event != -1){
		Assert(Timing_events[event].ref_count == 0);
		Timing_events[event].start = timer_get_microseconds();
		Timing_events[event].ref_count++;
	}

	else {
		if(Timing_event_count < MAX_TIMING_EVENTS){
			strcpy_s(Timing_events[Timing_event_count].name, event_name);
			Timing_events[Timing_event_count].start = timer_get_microseconds();
			Timing_events[Timing_event_count++].ref_count++;
		}
	}
#endif
}

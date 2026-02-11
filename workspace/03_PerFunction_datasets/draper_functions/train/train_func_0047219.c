timer_process_group(void *data)


{
    int widget;


    int interval = *((int *) data);


    if (nTimerGroups <= 0) {

	error("Huh? Not even a single timer group to process? Dazed and confused...");
	return;
    }


    if (nTimerGroupWidgets <= 0) {

	error("Huh? Not even a single widget slot to process? Dazed and confused...");
	return;
    }


    for (widget = 0; widget < nTimerGroupWidgets; widget++) {

	if (TimerGroupWidgets[widget].active == TIMER_INACTIVE)
	    continue;


	if (TimerGroupWidgets[widget].interval == interval) {


	    if (TimerGroupWidgets[widget].callback != NULL)
		TimerGroupWidgets[widget].callback(TimerGroupWidgets[widget].data);


	    if (TimerGroupWidgets[widget].one_shot) {
		TimerGroupWidgets[widget].active = TIMER_INACTIVE;


		timer_remove_empty_group(interval);
	    }
	}
    }
}

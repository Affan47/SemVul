MISC_handler (void)
{
	static bool dorecheck;
	bool recheck;
	int i;
	evt mintime;
	evt ct = get_cycles ();
	static int recursive;

	if (recursive) {
		dorecheck = true;
		return;
	}
	recursive++;
	eventtab[ev_misc].active = 0;
	recheck = true;
	while (recheck) {
		recheck = false;
		mintime = ~0L;
		for (i = 0; i < ev2_max; i++) {
			if (eventtab2[i].active) {
				if (eventtab2[i].evtime == ct) {
					eventtab2[i].active = false;
					eventtab2[i].handler (eventtab2[i].data);
					if (dorecheck || eventtab2[i].active) {
						recheck = true;
						dorecheck = false;
					}
				} else {
					evt eventtime = eventtab2[i].evtime - ct;
					if (eventtime < mintime)
						mintime = eventtime;
				}
			}
		}
	}
	if (mintime != ~0L) {
		eventtab[ev_misc].active = true;
		eventtab[ev_misc].oldcycles = ct;
		eventtab[ev_misc].evtime = ct + mintime;
		events_schedule ();
	}
	recursive--;
}

torture_rtmutex_boost(struct torture_random_state *trsp)
{
	int policy;
	struct sched_param param;
	const unsigned int factor = 50000;

	if (!rt_task(current)) {


		if (!(torture_random(trsp) %
		      (cxt.nrealwriters_stress * factor))) {
			policy = SCHED_FIFO;
			param.sched_priority = MAX_RT_PRIO - 1;
		} else
			return;
	} else {


		if (!trsp || !(torture_random(trsp) %
			       (cxt.nrealwriters_stress * factor * 2))) {
			policy = SCHED_NORMAL;
			param.sched_priority = 0;
		} else
			return;
	}

	sched_setscheduler_nocheck(current, policy, &param);
}

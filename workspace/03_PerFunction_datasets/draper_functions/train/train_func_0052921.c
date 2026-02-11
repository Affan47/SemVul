initialize_priority_and_scheduling (TrackerSchedIdle sched_idle,
                                    gboolean         first_time_index)
{

	if (sched_idle == TRACKER_SCHED_IDLE_ALWAYS ||
	    (sched_idle == TRACKER_SCHED_IDLE_FIRST_INDEX && first_time_index)) {
		tracker_sched_idle ();
	}


	tracker_ioprio_init ();


	g_message ("Setting priority nice level to 19");

	errno = 0;
	if (nice (19) == -1 && errno != 0) {
		const gchar *str = g_strerror (errno);

		g_message ("Couldn't set nice value to 19, %s",
		           str ? str : "no error given");
	}
}

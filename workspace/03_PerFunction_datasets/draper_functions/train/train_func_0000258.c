opal_progress_set_event_poll_rate(int polltime)
{
    OPAL_OUTPUT((debug_output, "progress: progress_set_event_poll_rate(%d)", polltime));

#if OPAL_PROGRESS_USE_TIMERS
    event_progress_delta = 0;
#  if OPAL_TIMER_USEC_NATIVE
    event_progress_last_time = opal_timer_base_get_usec();
#  else
    event_progress_last_time = opal_timer_base_get_cycles();
#  endif
#else
    event_progress_counter = event_progress_delta = 0;
#endif

    if (polltime == 0) {
#if OPAL_PROGRESS_USE_TIMERS

        event_progress_delta = 60 * 1000000;
#else

        event_progress_delta = INT_MAX;
#endif
    } else {
#if OPAL_PROGRESS_USE_TIMERS
        event_progress_delta = polltime;
#else


        event_progress_delta = polltime - 1;
#endif
    }

#if OPAL_PROGRESS_USE_TIMERS && !OPAL_TIMER_USEC_NATIVE

    event_progress_delta = event_progress_delta * opal_timer_base_get_freq() / 1000000;
#endif
}

crm_timer_start(fsa_timer_t * timer)
{
    const char *timer_desc = get_timer_desc(timer);

    if (timer->source_id == 0 && timer->period_ms > 0) {
        timer->source_id = g_timeout_add(timer->period_ms, timer->callback, (void *)timer);
        CRM_ASSERT(timer->source_id != 0);
        crm_debug("Started %s (%s:%dms), src=%d",
                  timer_desc, fsa_input2string(timer->fsa_input),
                  timer->period_ms, timer->source_id);

    } else if (timer->period_ms < 0) {
        crm_err("Tried to start %s (%s:%dms) with a -ve period",
                timer_desc, fsa_input2string(timer->fsa_input), timer->period_ms);

    } else {
        crm_debug("%s (%s:%dms) already running: src=%d",
                  timer_desc, fsa_input2string(timer->fsa_input),
                  timer->period_ms, timer->source_id);
        return FALSE;
    }
    return TRUE;
}

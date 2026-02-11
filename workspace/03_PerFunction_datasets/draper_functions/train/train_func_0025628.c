request_schedule_cpus(const char* where) {
    if (log_flags.cpu_sched_debug) {
        msg_printf(0, MSG_INFO, "[cpu_sched_debug] Request CPU reschedule: %s", where);
    }
    must_schedule_cpus = true;
}

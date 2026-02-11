add_task_handlers(Task *task, NotifierSignal *signal, int flags, const String &prefix)
{
    intptr_t task_offset = (uint8_t *)task - (uint8_t *)this;
    void *thunk = (void *)task_offset;
    add_read_handler(prefix + "scheduled", read_task_scheduled, thunk);
    if (flags & TASKHANDLER_WRITE_SCHEDULED)
	add_write_handler(prefix + "scheduled", write_task_scheduled, thunk);
#if HAVE_STRIDE_SCHED
    add_read_handler(prefix + "tickets", read_task_tickets, thunk);
    if (flags & TASKHANDLER_WRITE_TICKETS)
	add_write_handler(prefix + "tickets", write_task_tickets, thunk);
#endif
#if HAVE_MULTITHREAD
    add_read_handler(prefix + "home_thread", read_task_home_thread, thunk);
    if (flags & TASKHANDLER_WRITE_HOME_THREAD)
	add_write_handler(prefix + "home_thread", write_task_home_thread, thunk);
#endif
#if CLICK_DEBUG_SCHEDULING
    if (signal) {
	intptr_t signal_offset = (uint8_t *) signal - (uint8_t *) this;
	add_read_handler(prefix + "notifier", read_notifier_signal, (void *) signal_offset);
    }
#else
    (void) signal;
#endif
}

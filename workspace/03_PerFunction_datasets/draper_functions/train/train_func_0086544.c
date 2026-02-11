worker_signal_handler(int) {
#ifndef GETRUSAGE_IN_TIMER_THREAD
    getrusage(RUSAGE_SELF, &worker_thread_ru);
#endif
    if (worker_thread_exit_flag) {
        boinc_exit(worker_thread_exit_status);
    }
    if (options.direct_process_action) {
        while (boinc_status.suspended && in_critical_section==0) {
            sleep(1);
        }
    }
}

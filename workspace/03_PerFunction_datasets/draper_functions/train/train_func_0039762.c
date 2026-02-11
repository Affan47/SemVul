print_job_list(vector<RESULT*>& jobs) {
    for (unsigned int i=0; i<jobs.size(); i++) {
        RESULT* rp = jobs[i];
        msg_printf(rp->project, MSG_INFO,
            "[cpu_sched_debug] %d: %s (MD: %s; UTS: %s)",
            i, rp->name,
            rp->edf_scheduled?"yes":"no",
            rp->unfinished_time_slice?"yes":"no"
        );
    }
}

compute_may_have_work(PROJECT* p, int rsc_type) {
    if (dont_fetch(p, rsc_type)) return false;
    if (p->rsc_defer_sched[rsc_type]) return false;
    return (backoff_time < gstate.now);
}

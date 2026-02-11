clear_schedule_backoffs(ACTIVE_TASK* atp) {
    int rt = atp->result->avp->rsc_type();
    if (rt == RSC_TYPE_CPU) return;
    for (unsigned int i=0; i<gstate.results.size(); i++) {
        RESULT* rp = gstate.results[i];
        if (rp->avp->rsc_type() == rt) {
            rp->schedule_backoff = 0;
        }
    }
}

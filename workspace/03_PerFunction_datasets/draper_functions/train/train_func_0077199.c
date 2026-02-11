send_work_score() {
    for (int i=0; i<NPROC_TYPES; i++) {
        if (g_wreq->need_proc_type(i)) {
            send_work_score_type(i);
        }
    }
}

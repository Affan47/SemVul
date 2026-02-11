restore_others(int rt) {
    for (int i=0; i<NPROC_TYPES; i++) {
        if (i == rt) continue;
        g_wreq->req_secs[i] += req_sec_save[i];
        g_wreq->req_instances[i] += req_inst_save[i];
    }
}

upload_notify_app(FILE_INFO* fip) {
    for (unsigned int i=0; i<active_tasks.size(); i++) {
        ACTIVE_TASK* atp = active_tasks[i];
        RESULT* rp = atp->result;
        FILE_REF* frp = rp->lookup_file(fip);
        if (frp) {
            atp->upload_notify_app(fip, frp);
        }
    }
}

recovery_plan() {
    keep_present = false;
    if (present_on_server) {
        status = PRESENT;
        cost = 0;
    } else if (hosts.size() > 0) {


        status = RECOVERABLE;
        cost = size;
        if ((int)(hosts.size()) < parent->dfile->policy.replication) {
            data_needed = true;
        }
    } else {
        status = UNRECOVERABLE;
    }
    if (debug_status) {
        printf("   chunk %s: status %s\n", name, status_str(status));
    }
}

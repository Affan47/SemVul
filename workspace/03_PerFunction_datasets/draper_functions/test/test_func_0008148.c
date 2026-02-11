some_download_stalled() {
#ifndef SIM
    unsigned int i;
    FILE_INFO* fip;
    PERS_FILE_XFER* pfx;
    bool some_file_missing = false;

    for (i=0; i<wup->input_files.size(); i++) {
        fip = wup->input_files[i].file_info;
        if (fip->status != FILE_PRESENT) some_file_missing = true;
        pfx = fip->pers_file_xfer;
        if (pfx && pfx->next_request_time > gstate.now) {
            return true;
        }
    }
    for (i=0; i<avp->app_files.size(); i++) {
        fip = avp->app_files[i].file_info;
        if (fip->status != FILE_PRESENT) some_file_missing = true;
        pfx = fip->pers_file_xfer;
        if (pfx && pfx->next_request_time > gstate.now) {
            return true;
        }
    }

    if (some_file_missing && !project->download_backoff.ok_to_transfer()) {
        return true;
    }
#endif
    return false;
}

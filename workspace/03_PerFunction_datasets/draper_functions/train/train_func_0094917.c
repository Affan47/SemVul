handle_request(FILE* fin, FILE* fout, char* code_sign_key) {
    SCHEDULER_REQUEST sreq;
    SCHEDULER_REPLY sreply;
    char buf[1024];

    g_request = &sreq;
    g_reply = &sreply;
    g_wreq = &sreply.wreq;

    sreply.nucleus_only = true;

    log_messages.set_indent_level(1);

    MIOFILE mf;
    XML_PARSER xp(&mf);
    mf.init_file(fin);
    const char* p = sreq.parse(xp);
    double start_time = dtime();
    if (!p){
        process_request(code_sign_key);

        if ((config.locality_scheduling || config.locality_scheduler_fraction) && !sreply.nucleus_only) {
            send_file_deletes();
        }
    } else {
        sprintf(buf, "Error in request message: %s", p);
        log_incomplete_request();
        sreply.insert_message(buf, "low");
    }

    if (config.debug_user_messages) {
        log_user_messages();
    }

    sreply.write(fout, sreq);
    log_messages.printf(MSG_NORMAL,
        "Scheduler ran %.3f seconds\n", dtime()-start_time
    );

    if (strlen(config.sched_lockfile_dir)) {
        unlock_sched();
    }
}

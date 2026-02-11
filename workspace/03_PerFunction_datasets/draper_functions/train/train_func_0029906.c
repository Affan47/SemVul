handle_file(VDA_FILE_AUX& vf, DB_VDA_FILE& dvf) {
    int retval;
    char buf[1024];

    log_messages.printf(MSG_NORMAL, "processing file %s\n", vf.file_name);


    sprintf(buf, "%s/boinc_meta.txt", vf.dir);
    retval = vf.policy.parse(buf);
    if (retval) {
        log_messages.printf(MSG_CRITICAL, "Can't parse policy file %s\n", buf);
        return retval;
    }
    if (vf.initialized) {
        log_messages.printf(MSG_NORMAL, "Getting state\n");
        retval = vf.get_state();
        if (retval) {
            log_messages.printf(MSG_CRITICAL, "vf.get_state failed %d\n", retval);
            return retval;
        }
    } else {
        log_messages.printf(MSG_NORMAL, "Initializing\n");
        retval = vf.init();
        if (retval) {
            log_messages.printf(MSG_CRITICAL, "vf.init failed %d\n", retval);
            return retval;
        }
        sprintf(buf, "initialized=1, chunk_size=%.0f", vf.policy.chunk_size());
        dvf.update_field(buf);
    }
    log_messages.printf(MSG_NORMAL, "Recovery plan:\n");
    vf.meta_chunk->recovery_plan();


    if (vf.retrieving) {
        if (vf.retrieved) return 0;
        switch (vf.meta_chunk->status) {
        case PRESENT:


            retval = vf.meta_chunk->reconstruct();
            if (retval) {
                log_messages.printf(MSG_CRITICAL,
                    "reconstruct of %s failed: %d\n", vf.file_name, retval
                );
            } else {
                log_messages.printf(MSG_NORMAL,
                    "retrieval of %s completed successfully\n", vf.file_name
                );


                sprintf(buf, "truncate %s/%s --reference %s/%s",
                    vf.dir, vf.file_name, vf.dir, vf.file_name
                );
                retval = system(buf);
                if (retval) {
                    log_messages.printf(MSG_CRITICAL,
                        "Can't truncate %s: %d\n", vf.file_name, retval
                    );
                }
                dvf.retrieved = true;
                dvf.update();
            }
            break;
        case RECOVERABLE:


            vf.meta_chunk->upload_all();
            break;
        case UNRECOVERABLE:


            log_messages.printf(MSG_CRITICAL,
                "Can't retrieve %s: unrecoverable\n",
                vf.file_name
            );
            break;
        }
        return 0;
    }

    retval = vf.meta_chunk->decide_reconstruct();
    if (retval) {
        log_messages.printf(MSG_CRITICAL, "vf.decide_reconstruct failed %d\n", retval);
        return retval;
    }
    retval = vf.meta_chunk->reconstruct_and_cleanup();
    if (retval) {
        log_messages.printf(MSG_CRITICAL,
            "vf.reconstruct_and_cleanup failed %d\n", retval
        );
        return retval;
    }
    log_messages.printf(MSG_NORMAL, "Recovery action:\n");
    retval = vf.meta_chunk->recovery_action(dtime());
    if (retval) {
        log_messages.printf(MSG_CRITICAL, "vf.recovery_action failed %d\n", retval);
        return retval;
    }
    vf.meta_chunk->compute_min_failures();
    return 0;
}

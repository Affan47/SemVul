retrieve_single_trigger_by_fileset_name(char *fileset_name, DB_SCHED_TRIGGER& trigger) {
    int retval = 0;


    retval = trigger.select_unique_by_fileset_name(fileset_name);
    if(!retval) {
        if (config.debug_locality) {
            log_messages.printf(MSG_DEBUG,
                    "[locality] trigger %s state after retrieval: nw=%i wa=%i nwa=%i wsr=%i\n",
                    fileset_name,
                    trigger.need_work,
                    trigger.work_available,
                    trigger.no_work_available,
                    trigger.working_set_removal
            );
        }


        return true;
    }
    else if(retval == ERR_DB_NOT_FOUND) {
        log_messages.printf(MSG_NORMAL,
                "[locality] trigger retrieval for filename %s returned empty set\n", fileset_name
        );
        return false;
    }
    else {
        log_messages.printf(MSG_CRITICAL,
            "[locality] trigger retrieval for filename %s failed with error %s\n",
            fileset_name, boincerror(retval)
        );
        return false;
    }
}

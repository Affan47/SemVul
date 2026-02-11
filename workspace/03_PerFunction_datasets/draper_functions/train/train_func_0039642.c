globus_l_gram_condor_poll_callback(
    void *                              user_arg)
{
    int                                 rc;
    time_t                              last_poll_time;
    time_t                              poll_time;
    double                              poll_length;
    globus_reltime_t                    delay;
    globus_gram_job_manager_t *         manager = user_arg;
    globus_scheduler_event_t *          event;
    globus_fifo_t                       events;
    char *                              condor_log_data;
    globus_gram_job_manager_ref_t *     ref;
    uint64_t                            uniq1, uniq2;
    char *                              path = NULL;

    GlobusGramJobManagerLock(manager);
    poll_time = time(NULL);
    last_poll_time = manager->seg_last_timestamp;

    globus_gram_job_manager_log(
            manager,
            GLOBUS_GRAM_JOB_MANAGER_LOG_TRACE,
            "event=gram.condor_poll.start "
            "level=TRACE "
            "poll_time=%d "
            "last_poll=%d "
            "\n",
            poll_time,
            last_poll_time);

    rc = globus_fifo_init(&events);
    if (rc != GLOBUS_SUCCESS)
    {
        poll_time = last_poll_time;
    }


    for (ref = globus_hashtable_first(&manager->request_hash);
         ref != NULL;
         ref = globus_hashtable_next(&manager->request_hash))
    {
        if (ref->request &&
            ref->request->job_id_string &&
            *ref->request->job_id_string == 0)
        {

            continue;
        }
        rc = sscanf(ref->key, "/%" SCNu64 "/%" SCNu64 "/", &uniq1, &uniq2);
        if (rc != 2)
        {
            globus_gram_job_manager_log(
                    manager,
                    GLOBUS_GRAM_JOB_MANAGER_LOG_WARN,
                    "event=gram.condor_poll.info "
                    "level=WARN "
                    "msg=\"%s\" "
                    "key=\"%s\" "
                    "\n",
                    "Unexpected key format",
                    ref->key);
            continue;
        }

        path = globus_common_create_string("%s/condor.%"PRIu64".%"PRIu64,
                manager->config->job_state_file_dir,
                uniq1, uniq2);
        if (path == NULL)
        {
            continue;
        }

        rc = globus_l_condor_read_log(
                manager,
                path,
                ref->seg_last_size,
                &condor_log_data);


        if (rc != GLOBUS_SUCCESS || condor_log_data == NULL)
        {
            goto read_failed;
        }

        rc = globus_l_condor_parse_log(
                condor_log_data,
                ref,
                &events);

        free(condor_log_data);
read_failed:
        free(path);
        path = NULL;
    }


    poll_length = difftime(time(NULL), poll_time);
    if (poll_length > 1.0)
    {
        GlobusTimeReltimeSet(delay, (time_t) (poll_length * 5), 0);
    }
    else
    {
        GlobusTimeReltimeSet(delay, (time_t) 5, 0);
    }
    globus_callback_adjust_period(manager->fork_callback_handle, &delay);
    GlobusGramJobManagerUnlock(manager);

    while (!globus_fifo_empty(&events))
    {
        event = globus_fifo_dequeue(&events);

        globus_l_gram_seg_event_callback(manager, event);

        globus_scheduler_event_destroy(event);
    }
    globus_fifo_destroy(&events);

    GlobusGramJobManagerLock(manager);
    if (poll_time > manager->seg_last_timestamp)
    {
        manager->seg_last_timestamp = poll_time;
    }
    if (globus_l_condor_regexes_compiled)
    {
        regfree(&globus_l_condor_outer_re);
        regfree(&globus_l_condor_inner_re);
        globus_l_condor_regexes_compiled = GLOBUS_FALSE;
    }
    GlobusGramJobManagerUnlock(manager);
    globus_gram_job_manager_log(
            manager,
            GLOBUS_GRAM_JOB_MANAGER_LOG_TRACE,
            "event=gram.condor_poll.end "
            "level=TRACE "
            "\n");
}

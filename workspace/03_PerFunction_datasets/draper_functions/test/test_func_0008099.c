globus_gram_job_manager_add_reference_by_jobid(
    globus_gram_job_manager_t *         manager,
    const char *                        jobid,
    const char *                        reason,
    globus_gram_jobmanager_request_t ** request)
{
    int                                 rc = GLOBUS_SUCCESS;
    globus_result_t                     result;
    globus_gram_job_id_ref_t *          jobref;
    globus_list_t *                     pending_restart_ref;

    globus_gram_job_manager_log(
            manager,
            GLOBUS_GRAM_JOB_MANAGER_LOG_TRACE,
            "event=gram.add_reference_by_jobid.start "
            "level=TRACE "
            "jobid=\"%s\" "
            "reason=\"%s\" "
            "\n",
            jobid,
            reason);

    if (request)
    {
        *request = NULL;
    }

    if (manager->stop)
    {
        rc = GLOBUS_GRAM_PROTOCOL_ERROR_JM_STOPPED;

        globus_gram_job_manager_log(
                manager,
                GLOBUS_GRAM_JOB_MANAGER_LOG_WARN,
                "event=gram.add_reference_by_jobid.end "
                "level=WARN "
                "jobid=\"%s\" "
                "status=%d "
                "reason=\"%s\" "
                "\n",
                jobid,
                -rc,
                globus_gram_protocol_error_string(rc));

        goto stop;
    }

    jobref = globus_hashtable_lookup(&manager->job_id_hash, (void *) jobid);
    if (!jobref)
    {
        rc = GLOBUS_GRAM_PROTOCOL_ERROR_JOB_CONTACT_NOT_FOUND;

        globus_gram_job_manager_log(
                manager,
                GLOBUS_GRAM_JOB_MANAGER_LOG_DEBUG,
                "event=gram.add_reference_by_jobid.end "
                "level=DEBUG "
                "jobid=\"%s\" "
                "status=%d "
                "msg=\"%s\" "
                "reason=\"%s\" "
                "\n",
                jobid,
                -rc,
                "Unknown job ID",
                globus_gram_protocol_error_string(rc));

        goto no_such_job;
    }

    rc = globus_l_gram_add_reference_locked(
            manager,
            jobref->job_contact_path,
            reason,
            request);

    if (rc != GLOBUS_SUCCESS)
    {
        globus_gram_job_manager_log(
                manager,
                GLOBUS_GRAM_JOB_MANAGER_LOG_ERROR,
                "event=gram.add_reference_by_jobid.end "
                "level=ERROR "
                "jobid=\"%s\" "
                "status=%d "
                "msg=\"%s\" "
                "reason=\"%s\" "
                "\n",
                jobid,
                -rc,
                "Adding reference failed",
                globus_gram_protocol_error_string(rc));
        goto failed_add;
    }


    if ((*request) != NULL && (pending_restart_ref =
                globus_list_search_pred(manager->pending_restarts,
                        globus_hashtable_string_keyeq,
                        (*request)->job_contact_path)) != NULL)
    {
        globus_list_remove(&manager->pending_restarts, pending_restart_ref);

        rc = globus_l_gram_add_reference_locked(
                manager,
                jobref->job_contact_path,
                "state machine",
                request);
        if (rc != GLOBUS_SUCCESS)
        {
            goto remove_reference;
        }
        if ((*request)->restart_state == GLOBUS_GRAM_JOB_MANAGER_STATE_POLL_QUERY1 ||
            (*request)->restart_state == GLOBUS_GRAM_JOB_MANAGER_STATE_POLL_QUERY2 ||
            (*request)->restart_state == GLOBUS_GRAM_JOB_MANAGER_STATE_POLL1 ||
            (*request)->restart_state == GLOBUS_GRAM_JOB_MANAGER_STATE_POLL2)
        {
            globus_gram_job_manager_seg_pause(manager);
        }
        result = globus_callback_register_oneshot(
                &(*request)->poll_timer,
                NULL,
                globus_gram_job_manager_state_machine_callback,
                *request);
        if (result != GLOBUS_SUCCESS)
        {
            rc = GLOBUS_GRAM_PROTOCOL_ERROR_MALLOC_FAILED;
            globus_l_gram_job_manager_remove_reference_locked(
                    manager,
                    jobref->job_contact_path,
                    "state machine");
        }
    }

remove_reference:
    if (rc != GLOBUS_SUCCESS)
    {
        globus_l_gram_job_manager_remove_reference_locked(
                manager,
                jobref->job_contact_path,
                reason);
    }
    else
    {
        globus_gram_job_manager_log(
                manager,
                GLOBUS_GRAM_JOB_MANAGER_LOG_TRACE,
                "event=gram.add_reference_by_jobid.end "
                "level=TRACE "
                "jobid=\"%s\" "
                "status=%d "
                "\n",
                jobid,
                0);
    }

failed_add:
no_such_job:
stop:

    return rc;
}

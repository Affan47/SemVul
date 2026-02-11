globus_l_gram_job_manager_query_done(
    void *                              arg,
    globus_gram_jobmanager_request_t *  request,
    int                                 failure_code,
    int                                 starting_jobmanager_state,
    const char *                        variable,
    const char *                        value)
{
    int                                 script_status;
    globus_gram_job_manager_query_t *   query;
    globus_reltime_t                    delay;
    int                                 rc;

    query = arg;

    GlobusGramJobManagerRequestLock(request);

    if(failure_code)
    {
        request->failure_code = failure_code;
    }
    if(!variable)
    {
        GlobusTimeReltimeSet(delay, 0, 0);
        rc = globus_gram_job_manager_state_machine_register(
                request->manager,
                request,
                &delay);
    }
    else if(strcmp(variable, "GRAM_SCRIPT_ERROR") == 0)
    {
        script_status = atoi(value);

        if(script_status <= 0)
        {
            query->failure_code =
                GLOBUS_GRAM_PROTOCOL_ERROR_INVALID_SCRIPT_STATUS;
        }
        else
        {
            query->failure_code = script_status;
        }
    }
    else if(strcmp(variable, "GRAM_SCRIPT_JOB_STATE") == 0)
    {
        script_status = atoi(value);

        if(script_status <= 0)
        {
            query->failure_code =
                GLOBUS_GRAM_PROTOCOL_ERROR_INVALID_SCRIPT_STATUS;
        }
        else if((query->type == GLOBUS_GRAM_JOB_MANAGER_CANCEL ||
                query->signal == GLOBUS_GRAM_PROTOCOL_JOB_SIGNAL_CANCEL) &&
                (globus_i_gram_job_manager_script_valid_state_change(
                    request, script_status)))
        {
            request->unsent_status_change = GLOBUS_TRUE;
            globus_gram_job_manager_request_set_status(request, script_status);
            if(request->status == GLOBUS_GRAM_PROTOCOL_JOB_STATE_FAILED)
            {
                request->failure_code =
                    GLOBUS_GRAM_PROTOCOL_ERROR_USER_CANCELLED;
                query->failure_code =
                    GLOBUS_GRAM_PROTOCOL_ERROR_USER_CANCELLED;
            }
        }
        else if((query->signal == GLOBUS_GRAM_PROTOCOL_JOB_SIGNAL_SUSPEND ||
                query->signal == GLOBUS_GRAM_PROTOCOL_JOB_SIGNAL_RESUME) &&
                globus_i_gram_job_manager_script_valid_state_change(
                                                 request,
                                                 script_status))

        {
            globus_gram_job_manager_request_set_status(request, script_status);
            request->unsent_status_change = GLOBUS_TRUE;
        }
    }
    else if(strcmp(variable, "GRAM_SCRIPT_LOG") == 0)
    {
        if (request->job_log_level & GLOBUS_GRAM_JOB_MANAGER_LOG_DEBUG)
        {
            globus_gram_job_manager_request_log(
                    request,
                    GLOBUS_GRAM_JOB_MANAGER_LOG_DEBUG,
                    "event=gram.script.log "
                    "level=DEBUG "
                    "%s "
                    "\n",
                    value);
        }
    }
    else
    {
        query->failure_code =
            GLOBUS_GRAM_PROTOCOL_ERROR_INVALID_SCRIPT_STATUS;
    }

    GlobusGramJobManagerRequestUnlock(request);
}

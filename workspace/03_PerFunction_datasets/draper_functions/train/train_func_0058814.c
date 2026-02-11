globus_l_gram_job_manager_unregister(
    globus_gram_jobmanager_request_t *  request,
    const char *                        url,
    globus_gram_protocol_handle_t       handle)

{
    int rc;

    if (globus_l_gram_job_manager_is_done(request))
    {
       rc = GLOBUS_GRAM_PROTOCOL_ERROR_JOB_QUERY_DENIAL;
    }
    else if (!url || strlen(url) == 0)
    {
        rc = GLOBUS_GRAM_PROTOCOL_ERROR_HTTP_UNPACK_FAILED;
    }
    else
    {
        rc = globus_gram_job_manager_contact_remove(request, url);


        if (!request->client_contacts &&
             request->jobmanager_state == GLOBUS_GRAM_JOB_MANAGER_STATE_TWO_PHASE_END)
        {
            globus_bool_t reply=GLOBUS_TRUE;
            char buf[32];

            snprintf(buf,sizeof(buf),"%d",GLOBUS_GRAM_PROTOCOL_JOB_SIGNAL_COMMIT_END);
            globus_l_gram_job_manager_signal(request,buf,handle,&reply);
            globus_assert(reply == GLOBUS_TRUE);
        }
    }
    return rc;
}

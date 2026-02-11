globus_i_gram_parse_log_levels(
    const char *                        unparsed_string,
    int *                               log_levels,
    char **                             error_string)
{
    char *                  log_level_string = strdup(unparsed_string);
    char *                  level_string = NULL;
    char *                  last_string = NULL;
    int                     rc = GLOBUS_SUCCESS;

    if (log_level_string == NULL)
    {
        rc = GLOBUS_GRAM_PROTOCOL_ERROR_MALLOC_FAILED;

        goto error_exit;
    }
    if (error_string != NULL)
    {
        *error_string = NULL;
    }
    *log_levels = 0;

    for (level_string = strtok_r(log_level_string, "|", &last_string);
         level_string != NULL;
         level_string = strtok_r(NULL, "|", &last_string))
    {
        if (strcmp(level_string, "FATAL") == 0)
        {
            *log_levels |= GLOBUS_GRAM_JOB_MANAGER_LOG_FATAL;
        }
        else if (strcmp(level_string, "ERROR") == 0)
        {
            *log_levels |= GLOBUS_GRAM_JOB_MANAGER_LOG_ERROR;
        }
        else if (strcmp(level_string, "WARN") == 0)
        {
            *log_levels |= GLOBUS_GRAM_JOB_MANAGER_LOG_WARN;
        }
        else if (strcmp(level_string, "INFO") == 0)
        {
            *log_levels |= GLOBUS_GRAM_JOB_MANAGER_LOG_INFO;
        }
        else if (strcmp(level_string, "DEBUG") == 0)
        {
            *log_levels |= GLOBUS_GRAM_JOB_MANAGER_LOG_DEBUG;
        }
        else if (strcmp(level_string, "TRACE") == 0)
        {
            *log_levels |= GLOBUS_GRAM_JOB_MANAGER_LOG_TRACE;
        }
        else
        {
            globus_gram_job_manager_log(
                    NULL,
                    GLOBUS_GRAM_JOB_MANAGER_LOG_ERROR,
                    "event=gram.config.info "
                    "level=ERROR "
                    "status=-1 "
                    "msg=\"%s\" "
                    "string=\"%s\" "
                    "error_at=\"%s\" "
                    "\n",
                    "Error parsing log level string",
                    unparsed_string,
                    level_string);

            rc = GLOBUS_GRAM_PROTOCOL_ERROR_GATEKEEPER_MISCONFIGURED;

            if (error_string != NULL)
            {
                *error_string = globus_common_create_string(
                        "Error parsing log level string '%s' at '%s'\n",
                        unparsed_string,
                        level_string);
            }
            break;
        }
    }
    free(log_level_string);

error_exit:
    return rc;
}

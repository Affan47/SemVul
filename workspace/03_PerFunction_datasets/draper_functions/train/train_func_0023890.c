globus_gram_job_manager_rsl_attribute_get_int_value(
    globus_rsl_t *                      rsl,
    const char *                        attribute,
    int *                               value_ptr)
{
    const char *                        s;
    char *                              end;
    int                                 rc = GLOBUS_SUCCESS;

    rc = globus_gram_job_manager_rsl_attribute_get_string_value(
            rsl,
            attribute,
            &s);

    if (rc != GLOBUS_SUCCESS)
    {
        goto get_literal_failed;
    }
    else if (s == NULL)
    {
        rc = GLOBUS_GRAM_PROTOCOL_ERROR_BAD_RSL;
        goto get_literal_failed;
    }

    errno = 0;
    *value_ptr = strtol(s, &end, 10);
    if (errno != 0 || strlen(end) != 0)
    {
        rc = GLOBUS_GRAM_PROTOCOL_ERROR_BAD_RSL;
get_literal_failed:
        *value_ptr = 0;
    }

    return rc;
}

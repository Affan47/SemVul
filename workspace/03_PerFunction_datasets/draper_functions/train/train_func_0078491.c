globus_gss_assist_map_and_authorize(
    gss_ctx_id_t                        context,
    char *                              service,
    char *                              desired_identity,
    char *                              identity_buffer,
    unsigned int                        identity_buffer_length)
{
    globus_object_t *                   error;
    globus_result_t                     result = GLOBUS_SUCCESS;
    globus_callout_handle_t             authz_handle;

    static char *                       _function_name_ =
        "globus_gss_assist_map_and_authorize";

    result = globus_l_gss_assist_gridmap_initialize(&authz_handle);
    if(result != GLOBUS_SUCCESS)
    {
        return result;
    }

    if(authz_handle == NULL)
    {
        return globus_l_gss_assist_gridmap_lookup(
            context,
            service,
            desired_identity,
            identity_buffer,
            identity_buffer_length,
            NULL);
    }
    else
    {
        result = globus_callout_call_type(authz_handle,
                                          GLOBUS_GENERIC_MAPPING_TYPE,
                                          context,
                                          service,
                                          desired_identity,
                                          identity_buffer,
                                          identity_buffer_length);

        if(result != GLOBUS_SUCCESS)
        {
            error = globus_error_get(result);

            if(globus_error_match(
                   error,
                   GLOBUS_CALLOUT_MODULE,
                   GLOBUS_CALLOUT_ERROR_TYPE_NOT_REGISTERED)
               == GLOBUS_TRUE)
            {
                globus_object_free(error);
                result = globus_l_gss_assist_gridmap_lookup(
                    context,
                    service,
                    desired_identity,
                    identity_buffer,
                    identity_buffer_length,
                    NULL);
                goto error;
            }
            else
            {
                result = globus_error_put(error);
                GLOBUS_GSI_GSS_ASSIST_ERROR_CHAIN_RESULT(
                    result,
                    GLOBUS_GSI_GSS_ASSIST_CALLOUT_ERROR);
                goto error;
            }
        }

        result = globus_callout_call_type(authz_handle,
                                          GLOBUS_GENERIC_AUTHZ_TYPE,
                                          context,
                                          service);
        if(result != GLOBUS_SUCCESS)
        {
            error = globus_error_get(result);

            if(globus_error_match(
                   error,
                   GLOBUS_CALLOUT_MODULE,
                   GLOBUS_CALLOUT_ERROR_TYPE_NOT_REGISTERED)
               == GLOBUS_FALSE)
            {
                result = globus_error_put(error);
                GLOBUS_GSI_GSS_ASSIST_ERROR_CHAIN_RESULT(
                    result,
                    GLOBUS_GSI_GSS_ASSIST_CALLOUT_ERROR);
                goto error;
            }
            else
            {
                result = GLOBUS_SUCCESS;
            }

            globus_object_free(error);
        }
    }


 error:
    return result;
}

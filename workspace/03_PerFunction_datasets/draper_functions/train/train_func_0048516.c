globus_gsi_cert_utils_get_base_name(
    X509_NAME *                         subject,
    STACK_OF(X509) *                    cert_chain)
{
    X509_NAME_ENTRY *                   ne;
    int                                 i;
    int                                 depth = 0;
    globus_result_t                     result = GLOBUS_SUCCESS;
    globus_gsi_cert_utils_cert_type_t   cert_type;
    static char *                       _function_name_ =
        "globus_gsi_cert_utils_get_base_name";
    GLOBUS_I_GSI_CERT_UTILS_DEBUG_ENTER;

    for(i = 0;i < sk_X509_num(cert_chain);i++)
    {
        result = globus_gsi_cert_utils_get_cert_type(
            sk_X509_value(cert_chain, i),
            &cert_type);

        if (result != GLOBUS_SUCCESS)
        {
            GLOBUS_GSI_CERT_UTILS_ERROR_CHAIN_RESULT(
                result,
                GLOBUS_GSI_CERT_UTILS_ERROR_DETERMINING_CERT_TYPE);
            goto exit;
        }

        if(GLOBUS_GSI_CERT_UTILS_IS_PROXY(cert_type) &&
           (GLOBUS_GSI_CERT_UTILS_IS_IMPERSONATION_PROXY(cert_type) ||
           GLOBUS_GSI_CERT_UTILS_IS_LIMITED_PROXY(cert_type)) )
        {
            depth++;
        }
        else
        {
            break;
        }
    }


    for(i=0;i<depth;i++)
    {
        ne = X509_NAME_delete_entry(subject,
                                    X509_NAME_entry_count(subject)-1);
        if(ne)
        {
            X509_NAME_ENTRY_free(ne);
        }
    }

 exit:
    GLOBUS_I_GSI_CERT_UTILS_DEBUG_EXIT;
    return GLOBUS_SUCCESS;
}

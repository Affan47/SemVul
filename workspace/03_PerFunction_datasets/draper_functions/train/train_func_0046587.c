_gss_ntlm_destroy_kcm_cred(gss_cred_id_t *cred_handle)
{
    krb5_storage *request, *response;
    krb5_data response_data;
    krb5_context context;
    krb5_error_code ret;
    ntlm_cred cred;

    cred = (ntlm_cred)*cred_handle;

    ret = krb5_init_context(&context);
    if (ret)
        return ret;

    ret = krb5_kcm_storage_request(context, KCM_OP_DEL_NTLM_CRED, &request);
    if (ret)
	goto out;

    ret = krb5_store_stringz(request, cred->username);
    if (ret)
	goto out;

    ret = krb5_store_stringz(request, cred->domain);
    if (ret)
	goto out;

    ret = krb5_kcm_call(context, request, &response, &response_data);
    if (ret)
	goto out;

    krb5_storage_free(request);
    krb5_storage_free(response);
    krb5_data_free(&response_data);

 out:
    krb5_free_context(context);

    return ret;
}

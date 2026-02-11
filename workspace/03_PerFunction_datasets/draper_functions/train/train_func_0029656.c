kdb_free_lib_handle(krb5_context kcontext)
{
    krb5_error_code status = 0;

    status = kdb_free_library(kcontext->dal_handle->lib_handle);
    if (status)
        return status;

    free_mkey_list(kcontext, kcontext->dal_handle->master_keylist);
    krb5_free_principal(kcontext, kcontext->dal_handle->master_princ);
    free(kcontext->dal_handle);
    kcontext->dal_handle = NULL;
    return 0;
}

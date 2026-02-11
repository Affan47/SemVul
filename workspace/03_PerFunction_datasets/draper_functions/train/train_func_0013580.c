kdb_delete_entry(kadm5_server_handle_t handle, krb5_principal name)
{
    krb5_error_code ret;

    ret = krb5_db_delete_principal(handle->context, name);
    if (ret == KRB5_KDB_NOENTRY)
        ret = 0;
    return ret;
}

krb5int_delete_principal_no_log(krb5_context kcontext,
                                krb5_principal search_for)
{
    kdb_vftabl *v;
    krb5_error_code status;

    status = get_vftabl(kcontext, &v);
    if (status)
        return status;
    if (v->delete_principal == NULL)
        return KRB5_PLUGIN_OP_NOTSUPP;
    return v->delete_principal(kcontext, search_for);
}

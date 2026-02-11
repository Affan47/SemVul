krb5_db2_lock(krb5_context context, int lockmode)
{
    if (!inited(context))
        return KRB5_KDB_DBNOTINITED;
    return ctx_lock(context, context->dal_handle->db_context, lockmode);
}

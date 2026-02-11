krb5_db_alloc(krb5_context kcontext, void *ptr, size_t size)
{
    krb5_error_code status;
    kdb_vftabl *v;

    status = get_vftabl(kcontext, &v);
    if (status)
        return NULL;
    return v->alloc(kcontext, ptr, size);
}

krb5_db2_merge_nra_iterator(krb5_pointer ptr, krb5_db_entry *entry)
{
    struct nra_context *nra = (struct nra_context *)ptr;
    kdb5_dal_handle *dal_handle = nra->kcontext->dal_handle;
    krb5_error_code retval;
    int changed;
    krb5_db_entry *s_entry;
    krb5_db2_context *dst_db;

    memset(&s_entry, 0, sizeof(s_entry));

    dst_db = dal_handle->db_context;
    dal_handle->db_context = nra->db_context;


    retval = krb5_db2_get_principal(nra->kcontext, entry->princ, 0, &s_entry);
    if (retval != 0) {

        dal_handle->db_context = dst_db;
        return 0;
    }


    krb5_db2_merge_principal(nra->kcontext, s_entry, entry, &changed);

    dal_handle->db_context = dst_db;


    if (changed) {
        retval = krb5_db2_put_principal(nra->kcontext, entry, NULL);
    } else {
        retval = 0;
    }

    return retval;
}

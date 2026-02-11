krb5_fcc_write(krb5_context context, krb5_ccache id, krb5_pointer buf, unsigned int len)
{
    int ret;

    k5_cc_mutex_assert_locked(context, &((krb5_fcc_data *) id->data)->lock);
    invalidate_cache((krb5_fcc_data *) id->data);

    ret = write(((krb5_fcc_data *)id->data)->file, (char *) buf, len);
    if (ret < 0)
        return krb5_fcc_interpret(context, errno);
    if ((unsigned int) ret != len)
        return KRB5_CC_WRITE;
    return KRB5_OK;
}

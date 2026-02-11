krb5_rc_dfl_destroy(krb5_context context, krb5_rcache id)
{
#ifndef NOIOSTUFF
    if (krb5_rc_io_destroy(context, &((struct dfl_data *) (id->data))->d))
        return KRB5_RC_IO;
#endif
    return krb5_rc_dfl_close(context, id);
}

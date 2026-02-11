krb5_fcc_close_file (krb5_context context, krb5_fcc_data *data)
{
    int ret;
    krb5_error_code retval;

    k5_cc_mutex_assert_locked(context, &data->lock);

    if (data->file == NO_FILE)
        return KRB5_FCC_INTERNAL;

    retval = krb5_unlock_file(context, data->file);
    ret = close (data->file);
    data->file = NO_FILE;
    if (retval)
        return retval;

    return ret ? krb5_fcc_interpret (context, errno) : 0;
}

krb5_ktfile_end_get(krb5_context context, krb5_keytab id, krb5_kt_cursor *cursor)
{
    krb5_error_code kerror;

    free(*cursor);
    KTLOCK(id);
    KTITERS(id)--;
    if (KTFILEP(id) != NULL && KTITERS(id) == 0)
        kerror = krb5_ktfileint_close(context, id);
    else
        kerror = 0;
    KTUNLOCK(id);
    return kerror;
}

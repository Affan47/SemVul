krb5_kt_default(krb5_context context, krb5_keytab *id)
{
    char defname[BUFSIZ];
    krb5_error_code retval;

    if ((retval = krb5_kt_default_name(context, defname, sizeof(defname))))
        return retval;
    return krb5_kt_resolve(context, defname, id);
}

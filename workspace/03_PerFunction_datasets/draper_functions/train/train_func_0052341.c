krb5_ktsrvtab_get_next(krb5_context context, krb5_keytab id, krb5_keytab_entry *entry, krb5_kt_cursor *cursor)
{
    long *fileoff = (long *)*cursor;
    krb5_keytab_entry cur_entry;
    krb5_error_code kerror;

    if (fseek(KTFILEP(id), *fileoff, 0) == -1)
        return KRB5_KT_END;
    if ((kerror = krb5_ktsrvint_read_entry(context, id, &cur_entry)))
        return kerror;
    *fileoff = ftell(KTFILEP(id));
    *entry = cur_entry;
    return 0;
}

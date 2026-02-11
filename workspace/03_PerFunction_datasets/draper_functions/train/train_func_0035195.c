krb5_ktsrvint_close(krb5_context context, krb5_keytab id)
{
    if (!KTFILEP(id))
        return 0;
    (void) fclose(KTFILEP(id));
    KTFILEP(id) = 0;
    return 0;
}

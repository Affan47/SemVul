ktest_make_sample_etype_info(krb5_etype_info_entry ***p)
{
    krb5_etype_info_entry **info;
    int i, len;
    char *str;

    info = ealloc(4 * sizeof(krb5_etype_info_entry *));
    for (i = 0; i < 3; i++) {
        info[i] = ealloc(sizeof(krb5_etype_info_entry));
        info[i]->etype = i;
        len = asprintf(&str, "Morton's #%d", i);
        if (len < 0)
            abort();
        info[i]->salt = (krb5_octet *)str;
        info[i]->length = len;
        info[i]->s2kparams.data = NULL;
        info[i]->s2kparams.length = 0;
        info[i]->magic = KV5M_ETYPE_INFO_ENTRY;
    }
    free(info[1]->salt);
    info[1]->length = KRB5_ETYPE_NO_SALT;
    info[1]->salt = 0;
    *p = info;
}

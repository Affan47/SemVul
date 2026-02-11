krb5_ktsrvint_read_entry(krb5_context context, krb5_keytab id, krb5_keytab_entry *ret_entry)
{
    FILE *fp;
    char name[SNAME_SZ], instance[INST_SZ], realm[REALM_SZ];
    unsigned char key[8];
    int vno;
    krb5_error_code kerror;


    fp = KTFILEP(id);
    kerror = read_field(fp, name, sizeof(name));
    if (kerror != 0)
        return kerror;
    kerror = read_field(fp, instance, sizeof(instance));
    if (kerror != 0)
        return kerror;
    kerror = read_field(fp, realm, sizeof(realm));
    if (kerror != 0)
        return kerror;
    vno = getc(fp);
    if (vno == EOF)
        return KRB5_KT_END;
    if (fread(key, 1, sizeof(key), fp) != sizeof(key))
        return KRB5_KT_END;


    memset(ret_entry, 0, sizeof(*ret_entry));
    ret_entry->magic = KV5M_KEYTAB_ENTRY;
    kerror = krb5_425_conv_principal(context, name, instance, realm,
                                     &ret_entry->principal);
    if (kerror != 0)
        return kerror;
    ret_entry->vno = vno;
    ret_entry->timestamp = 0;
    ret_entry->key.enctype = ENCTYPE_DES_CBC_CRC;
    ret_entry->key.magic = KV5M_KEYBLOCK;
    ret_entry->key.length = sizeof(key);
    ret_entry->key.contents = k5memdup(key, sizeof(key), &kerror);
    if (ret_entry->key.contents == NULL) {
        krb5_free_principal(context, ret_entry->principal);
        return kerror;
    }

    return 0;
}

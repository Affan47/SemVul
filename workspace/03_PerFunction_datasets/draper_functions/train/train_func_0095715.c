hdb_write_master_key(krb5_context context, const char *filename,
		     hdb_master_key mkey)
{
    krb5_error_code ret;
    hdb_master_key p;
    krb5_keytab kt;

    if(filename == NULL)
	filename = HDB_DB_DIR "/m-key";

    ret = krb5_kt_resolve(context, filename, &kt);
    if(ret)
	return ret;

    for(p = mkey; p; p = p->next) {
	ret = krb5_kt_add_entry(context, kt, &p->keytab);
    }

    krb5_kt_close(context, kt);

    return ret;
}

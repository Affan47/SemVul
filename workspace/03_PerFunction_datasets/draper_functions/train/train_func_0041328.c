append_mit_key(krb5_context context, krb5_storage *sp,
               krb5_const_principal princ,
               unsigned int kvno, Key *key)
{
    krb5_error_code ret;
    krb5_salt k5salt;
    ssize_t sz;
    size_t key_versions = key->salt ? 2 : 1;
    size_t decrypted_key_length;
    char buf[2];
    krb5_data keylenbytes;
    unsigned int salttype;

    sz = append_string(context, sp, "\t%u\t%u\t%d\t%d\t", key_versions, kvno,
                        key->key.keytype, key->key.keyvalue.length + 2);
    if (sz == -1) return sz;
    ret = krb5_enctype_keysize(context, key->key.keytype, &decrypted_key_length);
    if (ret) return -1;
    buf[0] = decrypted_key_length & 0xff;
    buf[1] = (decrypted_key_length & 0xff00) >> 8;
    keylenbytes.data = buf;
    keylenbytes.length = sizeof (buf);
    sz = append_hex(context, sp, 1, 1, &keylenbytes);
    if (sz == -1) return sz;
    sz = append_hex(context, sp, 1, 1, &key->key.keyvalue);
    if (!key->salt)
        return sz;


    switch (key->salt->type) {
    case KRB5_PADATA_PW_SALT:


        ret = krb5_get_pw_salt(context, princ, &k5salt);
        if (ret) return -1;
        if (k5salt.saltvalue.length == key->salt->salt.length &&
            memcmp(k5salt.saltvalue.data, key->salt->salt.data,
                   k5salt.saltvalue.length) == 0)
            salttype = KRB5_KDB_SALTTYPE_NORMAL;
        else if (key->salt->salt.length == strlen(princ->realm) &&
                 memcmp(key->salt->salt.data, princ->realm,
                        key->salt->salt.length) == 0)
            salttype = KRB5_KDB_SALTTYPE_ONLYREALM;
        else if (key->salt->salt.length ==
		 k5salt.saltvalue.length - strlen(princ->realm) &&
                 memcmp((char *)k5salt.saltvalue.data + strlen(princ->realm),
                        key->salt->salt.data, key->salt->salt.length) == 0)
            salttype = KRB5_KDB_SALTTYPE_NOREALM;
        else
            salttype = KRB5_KDB_SALTTYPE_NORMAL;

	break;

    case KRB5_PADATA_AFS3_SALT:
        salttype = KRB5_KDB_SALTTYPE_AFS3;
	break;

    default:
	return -1;
    }

    sz = append_string(context, sp, "\t%u\t%u\t", salttype,
                       key->salt->salt.length);
    if (sz == -1) return sz;
    return append_hex(context, sp, 1, 1, &key->salt->salt);
}

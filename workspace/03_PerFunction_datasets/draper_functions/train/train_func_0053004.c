krb5_generate_subkey_extended(krb5_context context,
                              const krb5_keyblock *key,
                              krb5_enctype enctype,
                              krb5_keyblock **subkey)
{
    krb5_error_code retval;
    krb5_data seed;
    krb5_keyblock *keyblock;

    *subkey = NULL;

    seed = key2data(*key);
    retval = krb5_c_random_add_entropy(context, KRB5_C_RANDSOURCE_TRUSTEDPARTY,
                                       &seed);
    if (retval)
        return retval;

    keyblock = malloc(sizeof(krb5_keyblock));
    if (!keyblock)
        return ENOMEM;

    retval = krb5_c_make_random_key(context, enctype, keyblock);
    if (retval) {
        free(*subkey);
        return retval;
    }

    *subkey = keyblock;
    return 0;
}

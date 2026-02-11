mk_xorkey(krb5_key origkey, krb5_key *xorkey)
{
    krb5_error_code retval = 0;
    unsigned char *xorbytes;
    krb5_keyblock xorkeyblock;
    size_t i = 0;

    xorbytes = k5memdup(origkey->keyblock.contents, origkey->keyblock.length,
                        &retval);
    if (xorbytes == NULL)
        return retval;
    for (i = 0; i < origkey->keyblock.length; i++)
        xorbytes[i] ^= 0xf0;


    xorkeyblock = origkey->keyblock;
    xorkeyblock.contents = xorbytes;

    retval = krb5_k_create_key(0, &xorkeyblock, xorkey);
    zapfree(xorbytes, origkey->keyblock.length);
    return retval;
}

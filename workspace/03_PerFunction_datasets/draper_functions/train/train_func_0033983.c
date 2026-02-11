krb5int_c_copy_keyblock(krb5_context context, const krb5_keyblock *from,
                        krb5_keyblock **to)
{
    krb5_keyblock *new_key;
    krb5_error_code code;

    *to = NULL;
    new_key = malloc(sizeof(*new_key));
    if (!new_key)
        return ENOMEM;
    code = krb5int_c_copy_keyblock_contents(context, from, new_key);
    if (code) {
        free(new_key);
        return code;
    }
    *to = new_key;
    return 0;
}

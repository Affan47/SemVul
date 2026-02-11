krb5_auth_con_initivector(krb5_context context, krb5_auth_context auth_context)
{
    krb5_error_code ret;
    krb5_enctype enctype;

    if (auth_context->key == NULL)
        return EINVAL;
    ret = krb5_c_init_state(context, &auth_context->key->keyblock,
                            KRB5_KEYUSAGE_KRB_PRIV_ENCPART,
                            &auth_context->cstate);
    if (ret)
        return ret;


    enctype = krb5_k_key_enctype(context, auth_context->key);
    if (enctype == ENCTYPE_DES_CBC_CRC)
        zap(auth_context->cstate.data, auth_context->cstate.length);

    return 0;
}

krb5_auth_con_getrecvsubkey(krb5_context ctx, krb5_auth_context ac, krb5_keyblock **keyblock)
{
    if (ac->recv_subkey != NULL)
        return krb5_k_key_keyblock(ctx, ac->recv_subkey, keyblock);
    *keyblock = NULL;
    return 0;
}

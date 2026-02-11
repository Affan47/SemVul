krb5_free_priv_enc_part(krb5_context context, register krb5_priv_enc_part *val)
{
    if (val == NULL)
        return;
    free(val->user_data.data);
    krb5_free_address(context, val->r_address);
    krb5_free_address(context, val->s_address);
    free(val);
}

_gsskrb5i_get_acceptor_subkey(const gsskrb5_ctx ctx,
			      krb5_context context,
			      krb5_keyblock **key)
{
    krb5_error_code ret;
    *key = NULL;

    if (ctx->more_flags & LOCAL) {
	ret = krb5_auth_con_getremotesubkey(context,
				      ctx->auth_context,
				      key);
    } else {
	ret = krb5_auth_con_getlocalsubkey(context,
				     ctx->auth_context,
				     key);
    }
    if (ret == 0 && *key == NULL) {
	krb5_set_error_message(context, 0, "No acceptor subkey available");
	return GSS_KRB5_S_KG_NO_SUBKEY;
    }
    return ret;
}

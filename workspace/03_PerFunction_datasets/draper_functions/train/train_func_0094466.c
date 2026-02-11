krb5_authenticate (kx_context *kc, int s)
{
    krb5_auth_context auth_context = NULL;
    krb5_error_code ret;
    krb5_principal server;
    const char *host = kc->host;

    ret = krb5_sname_to_principal (CONTEXT(kc),
				   host, "host", KRB5_NT_SRV_HST, &server);
    if (ret) {
	krb5_warn (CONTEXT(kc), ret, "krb5_sname_to_principal: %s", host);
	return 1;
    }

    ret = krb5_sendauth (CONTEXT(kc),
			 &auth_context,
			 &s,
			 KX_VERSION,
			 NULL,
			 server,
			 AP_OPTS_MUTUAL_REQUIRED | AP_OPTS_USE_SUBKEY,
			 NULL,
			 NULL,
			 NULL,
			 NULL,
			 NULL,
			 NULL);
    if (ret) {
	if(ret != KRB5_SENDAUTH_BADRESPONSE)
	    krb5_warn (CONTEXT(kc), ret, "krb5_sendauth: %s", host);
	return 1;
    }

    ret = krb5_auth_con_getkey (CONTEXT(kc), auth_context,
				&K5DATA(kc)->keyblock);
    if (ret) {
	krb5_warn (CONTEXT(kc), ret, "krb5_auth_con_getkey: %s", host);
	krb5_auth_con_free (CONTEXT(kc), auth_context);
	return 1;
    }

    ret = krb5_crypto_init (CONTEXT(kc), K5DATA(kc)->keyblock,
			    0, &K5DATA(kc)->crypto);
    if (ret) {
	krb5_warn (CONTEXT(kc), ret, "krb5_crypto_init");
	krb5_auth_con_free (CONTEXT(kc), auth_context);
	return 1;
    }
    return 0;
}

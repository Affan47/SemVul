krb5_ret_creds_tag(krb5_storage *sp,
		   krb5_creds *creds)
{
    krb5_error_code ret;
    int8_t dummy8;
    int32_t dummy32, header;

    memset(creds, 0, sizeof(*creds));

    ret = krb5_ret_int32 (sp, &header);
    if (ret) goto cleanup;

    if (header & SC_CLIENT_PRINCIPAL) {
	ret = krb5_ret_principal (sp,  &creds->client);
	if(ret) goto cleanup;
    }
    if (header & SC_SERVER_PRINCIPAL) {
	ret = krb5_ret_principal (sp,  &creds->server);
	if(ret) goto cleanup;
    }
    if (header & SC_SESSION_KEY) {
	ret = krb5_ret_keyblock (sp,  &creds->session);
	if(ret) goto cleanup;
    }
    ret = krb5_ret_times (sp,  &creds->times);
    if(ret) goto cleanup;
    ret = krb5_ret_int8 (sp,  &dummy8);
    if(ret) goto cleanup;
    ret = krb5_ret_int32 (sp,  &dummy32);
    if(ret) goto cleanup;


    {
	uint32_t mask = 0xffff0000;
	creds->flags.i = 0;
	creds->flags.b.anonymous = 1;
	if (creds->flags.i & mask)
	    mask = ~mask;
	if (dummy32 & mask)
	    dummy32 = bitswap32(dummy32);
    }
    creds->flags.i = dummy32;
    if (header & SC_ADDRESSES) {
	ret = krb5_ret_addrs (sp,  &creds->addresses);
	if(ret) goto cleanup;
    }
    if (header & SC_AUTHDATA) {
	ret = krb5_ret_authdata (sp,  &creds->authdata);
	if(ret) goto cleanup;
    }
    if (header & SC_TICKET) {
	ret = krb5_ret_data (sp,  &creds->ticket);
	if(ret) goto cleanup;
    }
    if (header & SC_SECOND_TICKET) {
	ret = krb5_ret_data (sp,  &creds->second_ticket);
	if(ret) goto cleanup;
    }

cleanup:
    if(ret) {
#if 0
	krb5_free_cred_contents(context, creds);
#endif
    }
    return ret;
}

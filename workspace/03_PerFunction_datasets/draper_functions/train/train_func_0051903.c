TS_RESP_CTX_set_status_info(TS_RESP_CTX *ctx,
				int status, const char *text)
	{
	TS_STATUS_INFO *si = NULL;
	ASN1_UTF8STRING *utf8_text = NULL;
	int ret = 0;

	if (!(si = TS_STATUS_INFO_new())) goto err;
	if (!ASN1_INTEGER_set(si->status, status)) goto err;
	if (text)
		{
		if (!(utf8_text = ASN1_UTF8STRING_new())
		    || !ASN1_STRING_set(utf8_text, text, strlen(text)))
			goto err;
		if (!si->text && !(si->text = sk_ASN1_UTF8STRING_new_null()))
			goto err;
		if (!sk_ASN1_UTF8STRING_push(si->text, utf8_text)) goto err;
		utf8_text = NULL;
		}
	if (!TS_RESP_set_status_info(ctx->response, si)) goto err;
	ret = 1;
 err:
	if (!ret)
		TSerr(TS_F_TS_RESP_CTX_SET_STATUS_INFO, ERR_R_MALLOC_FAILURE);
	TS_STATUS_INFO_free(si);
	ASN1_UTF8STRING_free(utf8_text);
	return ret;
	}

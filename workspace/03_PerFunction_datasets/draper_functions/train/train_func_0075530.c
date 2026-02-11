TS_RESP_create_tst_info(TS_RESP_CTX *ctx,
					    ASN1_OBJECT *policy)
	{
	int result = 0;
	TS_TST_INFO *tst_info = NULL;
	ASN1_INTEGER *serial = NULL;
	ASN1_GENERALIZEDTIME *asn1_time = NULL;
	long sec, usec;
	TS_ACCURACY *accuracy = NULL;
	const ASN1_INTEGER *nonce;
	GENERAL_NAME *tsa_name = NULL;

	if (!(tst_info = TS_TST_INFO_new())) goto end;
	if (!TS_TST_INFO_set_version(tst_info, 1)) goto end;
	if (!TS_TST_INFO_set_policy_id(tst_info, policy)) goto end;
	if (!TS_TST_INFO_set_msg_imprint(tst_info, ctx->request->msg_imprint))
		goto end;
	if (!(serial = (*ctx->serial_cb)(ctx, ctx->serial_cb_data))
	    || !TS_TST_INFO_set_serial(tst_info, serial))
		goto end;
	if (!(*ctx->time_cb)(ctx, ctx->time_cb_data, &sec, &usec)
            || !(asn1_time = TS_RESP_set_genTime_with_precision(NULL,
					sec, usec,
					ctx->clock_precision_digits))
	    || !TS_TST_INFO_set_time(tst_info, asn1_time))
		goto end;


	if ((ctx->seconds || ctx->millis || ctx->micros)
	    && !(accuracy = TS_ACCURACY_new()))
		goto end;

	if (ctx->seconds && !TS_ACCURACY_set_seconds(accuracy, ctx->seconds))
		goto end;
	if (ctx->millis && !TS_ACCURACY_set_millis(accuracy, ctx->millis))
		goto end;
	if (ctx->micros && !TS_ACCURACY_set_micros(accuracy, ctx->micros))
		goto end;
	if (accuracy && !TS_TST_INFO_set_accuracy(tst_info, accuracy))
		goto end;


	if ((ctx->flags & TS_ORDERING)
	    && !TS_TST_INFO_set_ordering(tst_info, 1))
		goto end;


	if ((nonce = TS_REQ_get_nonce(ctx->request)) != NULL
	    && !TS_TST_INFO_set_nonce(tst_info, nonce))
		goto end;


	if (ctx->flags & TS_TSA_NAME)
		{
		if (!(tsa_name = GENERAL_NAME_new())) goto end;
		tsa_name->type = GEN_DIRNAME;
		tsa_name->d.dirn =
			X509_NAME_dup(ctx->signer_cert->cert_info->subject);
		if (!tsa_name->d.dirn) goto end;
		if (!TS_TST_INFO_set_tsa(tst_info, tsa_name)) goto end;
		}

	result = 1;
 end:
	if (!result)
		{
		TS_TST_INFO_free(tst_info);
		tst_info = NULL;
		TSerr(TS_F_TS_RESP_CREATE_TST_INFO, TS_R_TST_INFO_SETUP_ERROR);
		TS_RESP_CTX_set_status_info_cond(ctx, TS_STATUS_REJECTION,
						 "Error during TSTInfo "
						 "generation.");
		}
	GENERAL_NAME_free(tsa_name);
	TS_ACCURACY_free(accuracy);
	ASN1_GENERALIZEDTIME_free(asn1_time);
	ASN1_INTEGER_free(serial);

	return tst_info;
	}

cb(int ok, X509_STORE_CTX *ctx)
	{
	int cert_error = X509_STORE_CTX_get_error(ctx);
	X509 *current_cert = X509_STORE_CTX_get_current_cert(ctx);

	if (!ok)
		{
		if (current_cert)
			{
			X509_NAME_print_ex_fp(stdout,
				X509_get_subject_name(current_cert),
				0, XN_FLAG_ONELINE);
			printf("\n");
			}
		printf("%serror %d at %d depth lookup:%s\n",
			X509_STORE_CTX_get0_parent_ctx(ctx) ? "[CRL path]" : "",
			cert_error,
			X509_STORE_CTX_get_error_depth(ctx),
			X509_verify_cert_error_string(cert_error));
		switch(cert_error)
			{
			case X509_V_ERR_NO_EXPLICIT_POLICY:
				policies_print(NULL, ctx);
			case X509_V_ERR_CERT_HAS_EXPIRED:


			case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:

			case X509_V_ERR_INVALID_CA:
			case X509_V_ERR_INVALID_NON_CA:
			case X509_V_ERR_PATH_LENGTH_EXCEEDED:
			case X509_V_ERR_INVALID_PURPOSE:
			case X509_V_ERR_CRL_HAS_EXPIRED:
			case X509_V_ERR_CRL_NOT_YET_VALID:
			case X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION:
			ok = 1;

			}

		return ok;

		}
	if (cert_error == X509_V_OK && ok == 2)
		policies_print(NULL, ctx);
	if (!v_verbose)
		ERR_clear_error();
	return(ok);
	}

TS_check_signing_certs(PKCS7_SIGNER_INFO *si, STACK_OF(X509) *chain)
	{
	ESS_SIGNING_CERT *ss = ESS_get_signing_cert(si);
	STACK_OF(ESS_CERT_ID) *cert_ids = NULL;
	X509 *cert;
	int i = 0;
	int ret = 0;

	if (!ss) goto err;
	cert_ids = ss->cert_ids;

	cert = sk_X509_value(chain, 0);
	if (TS_find_cert(cert_ids, cert) != 0) goto err;


	if (sk_ESS_CERT_ID_num(cert_ids) > 1)
		{

		for (i = 1; i < sk_X509_num(chain); ++i)
			{
			cert = sk_X509_value(chain, i);
			if (TS_find_cert(cert_ids, cert) < 0) goto err;
			}
		}
	ret = 1;
 err:
	if (!ret)
		TSerr(TS_F_TS_CHECK_SIGNING_CERTS,
		      TS_R_ESS_SIGNING_CERTIFICATE_ERROR);
	ESS_SIGNING_CERT_free(ss);
	return ret;
	}

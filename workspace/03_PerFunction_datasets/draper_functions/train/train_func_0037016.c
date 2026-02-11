print_ocsp_summary(BIO *out, OCSP_BASICRESP *bs, OCSP_REQUEST *req,
			      STACK_OF(OPENSSL_STRING) *names,
			      STACK_OF(OCSP_CERTID) *ids, long nsec,
			      long maxage)
	{
	OCSP_CERTID *id;
	char *name;
	int i;

	int status, reason;

	ASN1_GENERALIZEDTIME *rev, *thisupd, *nextupd;

	if (!bs || !req || !sk_OPENSSL_STRING_num(names) || !sk_OCSP_CERTID_num(ids))
		return 1;

	for (i = 0; i < sk_OCSP_CERTID_num(ids); i++)
		{
		id = sk_OCSP_CERTID_value(ids, i);
		name = sk_OPENSSL_STRING_value(names, i);
		BIO_printf(out, "%s: ", name);

		if(!OCSP_resp_find_status(bs, id, &status, &reason,
					&rev, &thisupd, &nextupd))
			{
			BIO_puts(out, "ERROR: No Status found.\n");
			continue;
			}


		if (!OCSP_check_validity(thisupd, nextupd, nsec, maxage))
			{
			BIO_puts(out, "WARNING: Status times invalid.\n");
			ERR_print_errors(out);
			}
		BIO_printf(out, "%s\n", OCSP_cert_status_str(status));

		BIO_puts(out, "\tThis Update: ");
		ASN1_GENERALIZEDTIME_print(out, thisupd);
		BIO_puts(out, "\n");

		if(nextupd)
			{
			BIO_puts(out, "\tNext Update: ");
			ASN1_GENERALIZEDTIME_print(out, nextupd);
			BIO_puts(out, "\n");
			}

		if (status != V_OCSP_CERTSTATUS_REVOKED)
			continue;

		if (reason != -1)
			BIO_printf(out, "\tReason: %s\n",
				OCSP_crl_reason_str(reason));

		BIO_puts(out, "\tRevocation Time: ");
		ASN1_GENERALIZEDTIME_print(out, rev);
		BIO_puts(out, "\n");
		}

	return 1;
	}

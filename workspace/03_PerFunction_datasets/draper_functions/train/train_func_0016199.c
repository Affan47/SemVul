receipt_request_print(BIO *out, CMS_ContentInfo *cms)
	{
	STACK_OF(CMS_SignerInfo) *sis;
	CMS_SignerInfo *si;
	CMS_ReceiptRequest *rr;
	int allorfirst;
	STACK_OF(GENERAL_NAMES) *rto, *rlist;
	ASN1_STRING *scid;
	int i, rv;
	sis = CMS_get0_SignerInfos(cms);
	for (i = 0; i < sk_CMS_SignerInfo_num(sis); i++)
		{
		si = sk_CMS_SignerInfo_value(sis, i);
		rv = CMS_get1_ReceiptRequest(si, &rr);
		BIO_printf(bio_err, "Signer %d:\n", i + 1);
		if (rv == 0)
			BIO_puts(bio_err, "  No Receipt Request\n");
		else if (rv < 0)
			{
			BIO_puts(bio_err, "  Receipt Request Parse Error\n");
			ERR_print_errors(bio_err);
			}
		else
			{
			char *id;
			int idlen;
			CMS_ReceiptRequest_get0_values(rr, &scid, &allorfirst,
							&rlist, &rto);
			BIO_puts(out, "  Signed Content ID:\n");
			idlen = ASN1_STRING_length(scid);
			id = (char *)ASN1_STRING_data(scid);
			BIO_dump_indent(out, id, idlen, 4);
			BIO_puts(out, "  Receipts From");
			if (rlist)
				{
				BIO_puts(out, " List:\n");
				gnames_stack_print(out, rlist);
				}
			else if (allorfirst == 1)
				BIO_puts(out, ": First Tier\n");
			else if (allorfirst == 0)
				BIO_puts(out, ": All\n");
			else
				BIO_printf(out, " Unknown (%d)\n", allorfirst);
			BIO_puts(out, "  Receipts To:\n");
			gnames_stack_print(out, rto);
			}
		if (rr)
			CMS_ReceiptRequest_free(rr);
		}
	}

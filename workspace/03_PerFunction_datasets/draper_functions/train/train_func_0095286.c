asn1_output_data(BIO *out, BIO *data, ASN1_VALUE *val, int flags,
					const ASN1_ITEM *it)
	{
	BIO *tmpbio;
	const ASN1_AUX *aux = it->funcs;
	ASN1_STREAM_ARG sarg;
	int rv = 1;


	if (!(flags & SMIME_DETACHED) || (flags & PKCS7_REUSE_DIGEST))
		{
		SMIME_crlf_copy(data, out, flags);
		return 1;
		}

	if (!aux || !aux->asn1_cb)
		{
		ASN1err(ASN1_F_ASN1_OUTPUT_DATA,
					ASN1_R_STREAMING_NOT_SUPPORTED);
		return 0;
		}

	sarg.out = out;
	sarg.ndef_bio = NULL;
	sarg.boundary = NULL;


	if (aux->asn1_cb(ASN1_OP_DETACHED_PRE, &val, it, &sarg) <= 0)
		return 0;


	SMIME_crlf_copy(data, sarg.ndef_bio, flags);


	if (aux->asn1_cb(ASN1_OP_DETACHED_POST, &val, it, &sarg) <= 0)
		rv = 0;


	while (sarg.ndef_bio != out)
		{
		tmpbio = BIO_pop(sarg.ndef_bio);
		BIO_free(sarg.ndef_bio);
		sarg.ndef_bio = tmpbio;
		}

	return rv;

	}

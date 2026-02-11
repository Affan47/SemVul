create_query(BIO *data_bio, char *digest, const EVP_MD *md,
			    const char *policy, int no_nonce, int cert)
	{
	int ret = 0;
	TS_REQ *ts_req = NULL;
	int len;
	TS_MSG_IMPRINT *msg_imprint = NULL;
	X509_ALGOR *algo = NULL;
	unsigned char *data = NULL;
	ASN1_OBJECT *policy_obj = NULL;
	ASN1_INTEGER *nonce_asn1 = NULL;


	if (!md && !(md = EVP_get_digestbyname("sha1"))) goto err;


	if (!(ts_req = TS_REQ_new())) goto err;


	if (!TS_REQ_set_version(ts_req, 1)) goto err;


	if (!(msg_imprint = TS_MSG_IMPRINT_new())) goto err;


	if (!(algo = X509_ALGOR_new())) goto err;
	if (!(algo->algorithm = OBJ_nid2obj(EVP_MD_type(md)))) goto err;
	if (!(algo->parameter = ASN1_TYPE_new())) goto err;
	algo->parameter->type = V_ASN1_NULL;
	if (!TS_MSG_IMPRINT_set_algo(msg_imprint, algo)) goto err;


	if ((len = create_digest(data_bio, digest, md, &data)) == 0)
		goto err;
	if (!TS_MSG_IMPRINT_set_msg(msg_imprint, data, len)) goto err;

	if (!TS_REQ_set_msg_imprint(ts_req, msg_imprint)) goto err;


	if (policy && !(policy_obj = txt2obj(policy))) goto err;
	if (policy_obj && !TS_REQ_set_policy_id(ts_req, policy_obj)) goto err;


	if (!no_nonce && !(nonce_asn1 = create_nonce(NONCE_LENGTH))) goto err;
	if (nonce_asn1 && !TS_REQ_set_nonce(ts_req, nonce_asn1)) goto err;


	if (!TS_REQ_set_cert_req(ts_req, cert)) goto err;

	ret = 1;
 err:
	if (!ret)
		{
		TS_REQ_free(ts_req);
		ts_req = NULL;
		BIO_printf(bio_err, "could not create query\n");
		}
	TS_MSG_IMPRINT_free(msg_imprint);
	X509_ALGOR_free(algo);
	OPENSSL_free(data);
	ASN1_OBJECT_free(policy_obj);
	ASN1_INTEGER_free(nonce_asn1);
	return ts_req;
	}

ocsp_find_signer_sk(STACK_OF(X509) *certs, OCSP_RESPID *id)
	{
	int i;
	unsigned char tmphash[SHA_DIGEST_LENGTH], *keyhash;
	X509 *x;


	if (id->type == V_OCSP_RESPID_NAME)
		return X509_find_by_subject(certs, id->value.byName);


	if (id->value.byKey->length != SHA_DIGEST_LENGTH) return NULL;
	keyhash = id->value.byKey->data;

	for (i = 0; i < sk_X509_num(certs); i++)
		{
		x = sk_X509_value(certs, i);
		X509_pubkey_digest(x, EVP_sha1(), tmphash, NULL);
		if(!memcmp(keyhash, tmphash, SHA_DIGEST_LENGTH))
			return x;
		}
	return NULL;
	}

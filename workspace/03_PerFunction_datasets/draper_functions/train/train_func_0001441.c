OCSP_request_add1_cert(OCSP_REQUEST *req, X509 *cert)
	{
	OCSP_SIGNATURE *sig;
	if (!req->optionalSignature)
		req->optionalSignature = OCSP_SIGNATURE_new();
	sig = req->optionalSignature;
	if (!sig) return 0;
	if (!cert) return 1;
	if (!sig->certs && !(sig->certs = sk_X509_new_null()))
		return 0;

	if(!sk_X509_push(sig->certs, cert)) return 0;
	CRYPTO_add(&cert->references, 1, CRYPTO_LOCK_X509);
	return 1;
	}

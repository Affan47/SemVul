build_requestList(private_x509_ocsp_request_t *this)
{
	chunk_t issuerNameHash, issuerKeyHash;
	identification_t *issuer;
	x509_t *x509;
	certificate_t *cert;
	chunk_t list = chunk_empty;
	public_key_t *public;

	cert = (certificate_t*)this->ca;
	public = cert->get_public_key(cert);
	if (public)
	{
		hasher_t *hasher = lib->crypto->create_hasher(lib->crypto, HASH_SHA1);
		if (hasher)
		{
			if (public->get_fingerprint(public, KEYID_PUBKEY_SHA1,
										&issuerKeyHash))
			{
				enumerator_t *enumerator;

				issuer = cert->get_subject(cert);
				if (hasher->allocate_hash(hasher, issuer->get_encoding(issuer),
										  &issuerNameHash))
				{
					enumerator = this->candidates->create_enumerator(
															this->candidates);
					while (enumerator->enumerate(enumerator, &x509))
					{
						chunk_t request, serialNumber;

						serialNumber = x509->get_serial(x509);
						request = build_Request(this, issuerNameHash,
												issuerKeyHash, serialNumber);
						list = chunk_cat("mm", list, request);
					}
					enumerator->destroy(enumerator);
					chunk_free(&issuerNameHash);
				}
				hasher->destroy(hasher);
			}
		}
		else
		{
			DBG1(DBG_LIB, "creating OCSP request failed, SHA1 not supported");
		}
		public->destroy(public);
	}
	else
	{
		DBG1(DBG_LIB, "creating OCSP request failed, CA certificate has "
			 "no public key");
	}
	return asn1_wrap(ASN1_SEQUENCE, "m", list);
}

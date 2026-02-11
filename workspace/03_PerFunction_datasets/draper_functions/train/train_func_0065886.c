build_issuerAndSerialNumber(certificate_t *cert)
{
	identification_t *issuer = cert->get_issuer(cert);
	chunk_t serial = chunk_empty;

	if (cert->get_type(cert) == CERT_X509)
	{
		x509_t *x509 = (x509_t*)cert;
		serial = x509->get_serial(x509);
	}

	return asn1_wrap(ASN1_SEQUENCE, "cm",
					 issuer->get_encoding(issuer),
					 asn1_integer("c", serial));
}

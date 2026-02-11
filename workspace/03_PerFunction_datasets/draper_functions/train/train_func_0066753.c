certificate_read_server_certificate(rdpCertificate* certificate, uint8* server_cert, int length)
{
	STREAM* s;
	uint32 dwVersion;

	s = stream_new(0);
	s->p = s->data = server_cert;

	if (length < 1)
	{
		printf("null server certificate\n");
		return;
	}

	stream_read_uint32(s, dwVersion);

	switch (dwVersion & CERT_CHAIN_VERSION_MASK)
	{
		case CERT_CHAIN_VERSION_1:
			certificate_read_server_proprietary_certificate(certificate, s);
			break;

		case CERT_CHAIN_VERSION_2:
			certificate_read_server_x509_certificate_chain(certificate, s);
			break;

		default:
			printf("invalid certificate chain version:%d\n", dwVersion & CERT_CHAIN_VERSION_MASK);
			break;
	}
}

NETSCAPE_SPKI_b64_decode(const char *str, int len)
{
	unsigned char *spki_der;
	const unsigned char *p;
	int spki_len;
	NETSCAPE_SPKI *spki;
	if(len <= 0) len = strlen(str);
	if (!(spki_der = OPENSSL_malloc(len + 1))) {
		X509err(X509_F_NETSCAPE_SPKI_B64_DECODE, ERR_R_MALLOC_FAILURE);
		return NULL;
	}
	spki_len = EVP_DecodeBlock(spki_der, (const unsigned char *)str, len);
	if(spki_len < 0) {
		X509err(X509_F_NETSCAPE_SPKI_B64_DECODE,
						X509_R_BASE64_DECODE_ERROR);
		OPENSSL_free(spki_der);
		return NULL;
	}
	p = spki_der;
	spki = d2i_NETSCAPE_SPKI(NULL, &p, spki_len);
	OPENSSL_free(spki_der);
	return spki;
}

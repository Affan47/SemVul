NETSCAPE_SPKI_b64_encode(NETSCAPE_SPKI *spki)
{
	unsigned char *der_spki, *p;
	char *b64_str;
	int der_len;
	der_len = i2d_NETSCAPE_SPKI(spki, NULL);
	der_spki = OPENSSL_malloc(der_len);
	b64_str = OPENSSL_malloc(der_len * 2);
	if(!der_spki || !b64_str) {
		X509err(X509_F_NETSCAPE_SPKI_B64_ENCODE, ERR_R_MALLOC_FAILURE);
		return NULL;
	}
	p = der_spki;
	i2d_NETSCAPE_SPKI(spki, &p);
	EVP_EncodeBlock((unsigned char *)b64_str, der_spki, der_len);
	OPENSSL_free(der_spki);
	return b64_str;
}

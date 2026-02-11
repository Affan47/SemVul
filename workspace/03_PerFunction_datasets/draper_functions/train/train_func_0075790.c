pdf_open_crypt_imp(fz_stream *chain, pdf_crypt *crypt, pdf_crypt_filter *stmf, int num, int gen)
{
	unsigned char key[32];
	int len;

	crypt->ctx = chain->ctx;
	len = pdf_compute_object_key(crypt, stmf, num, gen, key);

	if (stmf->method == PDF_CRYPT_RC4)
		return fz_open_arc4(chain, key, len);

	if (stmf->method == PDF_CRYPT_AESV2 || stmf->method == PDF_CRYPT_AESV3)
		return fz_open_aesd(chain, key, len);

	return fz_open_copy(chain);
}

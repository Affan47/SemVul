evp_md_verify_signature(hx509_context context,
			const struct signature_alg *sig_alg,
			const Certificate *signer,
			const AlgorithmIdentifier *alg,
			const heim_octet_string *data,
			const heim_octet_string *sig)
{
    unsigned char digest[EVP_MAX_MD_SIZE];
    EVP_MD_CTX *ctx;
    size_t sigsize = EVP_MD_size(sig_alg->evp_md());

    if (sig->length != sigsize || sigsize > sizeof(digest)) {
	hx509_set_error_string(context, 0, HX509_CRYPTO_SIG_INVALID_FORMAT,
			       "SHA256 sigature have wrong length");
	return HX509_CRYPTO_SIG_INVALID_FORMAT;
    }

    ctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(ctx, sig_alg->evp_md(), NULL);
    EVP_DigestUpdate(ctx, data->data, data->length);
    EVP_DigestFinal_ex(ctx, digest, NULL);
    EVP_MD_CTX_destroy(ctx);

    if (ct_memcmp(digest, sig->data, sigsize) != 0) {
	hx509_set_error_string(context, 0, HX509_CRYPTO_BAD_SIGNATURE,
			       "Bad %s sigature", sig_alg->name);
	return HX509_CRYPTO_BAD_SIGNATURE;
    }

    return 0;
}

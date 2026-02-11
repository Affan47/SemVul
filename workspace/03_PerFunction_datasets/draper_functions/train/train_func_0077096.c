pbkdf2(struct pbkdf_prf_algo *hash, const char *pass, int passlen,
    const unsigned char *salt, int saltlen,
    int keylen, unsigned char *out)
{
	const EVP_MD *md;
	int r;

	OpenSSL_add_all_algorithms();

	md = EVP_get_digestbyname(hash->name);
	if (md == NULL) {
		tc_log(1, "Hash %s not found\n", hash->name);
		return ENOENT;
	}
	r = PKCS5_PBKDF2_HMAC(pass, passlen, salt, saltlen,
	    hash->iteration_count, md, keylen, out);

	if (r == 0) {
		tc_log(1, "Error in PBKDF2\n");
		return EINVAL;
	}

	return 0;
}

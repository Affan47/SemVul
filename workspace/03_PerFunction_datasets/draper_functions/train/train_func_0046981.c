crypto_load_key(const char *key, const bool is_private)
{
	BIO *bio;
	EVP_PKEY *pkey;

	bio = BIO_new_mem_buf((void *)key, strlen(key));
	if (bio == NULL) {
            log_err("crypto_load_key: BIO_new_mem_buf() failed\n");
	    return NULL;
	}


        if (is_private) {
            pkey = PEM_read_bio_PrivateKey(bio, NULL, NULL, NULL);
        } else {
            pkey = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
        }
        BIO_free(bio);
        if (pkey == NULL) {
            log_err("crypto_load_key: loading and parsing key failed\n");
            ERR_print_errors_fp(stderr);
            return NULL;
        }

        return pkey;
}

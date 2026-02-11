encrypt(EVP_CIPHER_CTX* ctx, uint8_t* out, const uint8_t* in)
	{
	int outl;

	if ( EVP_EncryptUpdate(ctx, out, &outl, in, 16) )
		return;

	char buf[120];
	ERR_error_string_n(ERR_get_error(), buf, sizeof(buf));
	fprintf(stderr, "Failed to encrypt: %s\n", buf);
	exit(1);
	}

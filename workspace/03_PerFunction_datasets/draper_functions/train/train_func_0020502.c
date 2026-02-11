des_cbc_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
			  const unsigned char *in, size_t inl)
{
	while(inl>=EVP_MAXCHUNK)
		{
		DES_ncbc_encrypt(in, out, (long)EVP_MAXCHUNK, ctx->cipher_data,
				(DES_cblock *)ctx->iv, ctx->encrypt);
		inl-=EVP_MAXCHUNK;
		in +=EVP_MAXCHUNK;
		out+=EVP_MAXCHUNK;
		}
	if (inl)
		DES_ncbc_encrypt(in, out, (long)inl, ctx->cipher_data,
				(DES_cblock *)ctx->iv, ctx->encrypt);
	return 1;
}

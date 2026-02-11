CRYPTO_cfb128_8_encrypt(const unsigned char *in, unsigned char *out,
			size_t length, const void *key,
			unsigned char ivec[16], int *num,
			int enc, block128_f block)
{
    size_t n;

    assert(in && out && key && ivec && num);
    assert(*num == 0);

    for(n=0 ; n<length ; ++n)
	cfbr_encrypt_block(&in[n],&out[n],8,key,ivec,enc,block);
}

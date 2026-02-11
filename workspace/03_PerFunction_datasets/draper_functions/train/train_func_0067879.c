twofish_get_info(int algo, size_t *keylen,
		 size_t *blocksize, size_t *contextsize,
		 int (**r_setkey) (void *c, const byte *key, unsigned keylen),
		 void (**r_encrypt) (void *c, byte *outbuf, const byte *inbuf),
		 void (**r_decrypt) (void *c, byte *outbuf, const byte *inbuf)
		 )
{
    *keylen = algo==10? 256 : 128;
    *blocksize = 16;
    *contextsize = sizeof (TWOFISH_context);

    *r_setkey = twofish_setkey;
    *r_encrypt = twofish_encrypt;
    *r_decrypt = twofish_decrypt;

    if( algo == 10 )
	return "TWOFISH";
    if (algo == 102)

	return "TWOFISH128";
    return NULL;
}

hmac_md5_init(HMAC_MD5_CTX *hmac,
		   const unsigned char *key,
		   int key_len)
{
  unsigned char k_ipad[65];


  unsigned char k_opad[65];


  unsigned char tk[16];
  int i;

  if (key_len > 64) {

    MD5_CTX      tctx;

    MD5Init(&tctx);
    MD5Update(&tctx, key, key_len);
    MD5Final(tk, &tctx);

    key = tk;
    key_len = 16;
  }


  MD5_memset(k_ipad, '\0', sizeof k_ipad);
  MD5_memset(k_opad, '\0', sizeof k_opad);
  MD5_memcpy( k_ipad, key, key_len);
  MD5_memcpy( k_opad, key, key_len);


  for (i=0; i<64; i++) {
    k_ipad[i] ^= 0x36;
    k_opad[i] ^= 0x5c;
  }

  MD5Init(&hmac->ictx);
  MD5Update(&hmac->ictx, k_ipad, 64);

  MD5Init(&hmac->octx);
  MD5Update(&hmac->octx, k_opad, 64);


  MD5_memset(&k_ipad[0], 0, sizeof(k_ipad));
  MD5_memset(&k_opad[0], 0, sizeof(k_opad));
  MD5_memset(&tk[0], 0, sizeof(tk));


}

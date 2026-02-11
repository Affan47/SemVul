mk_rsa(int rsa_key_bits, char **public_key, char **private_key)
{
  int len, st;
  unsigned char *buf, *next;
  unsigned long e_value = RSA_F4;
  RSA *rsa;

#if (OPENSSL_VERSION_NUMBER >= 0x0090800fL)
  int i;
  BIGNUM *e;
  BN_GENCB cb;

  rsa = RSA_new();
  e = BN_new();
  for (i = 0; i < sizeof(unsigned long) * 8; i++) {
	if (e_value & (1UL << i))
	  BN_set_bit(e, i);
  }

  BN_GENCB_set_old(&cb, NULL, NULL);
  st = RSA_generate_key_ex(rsa, rsa_key_bits, e, &cb);
  BN_free(e);
#else
  rsa = RSA_generate_key(rsa_key_bits, e_value, NULL, NULL);
  if (RSA_check_key(rsa) <= 0)
	st = 0;
  else
	st = 1;
#endif

  if (st == 0) {
	ERR_print_errors_fp(stderr);
	fprintf(stderr,
			"RSA key generation failed -- please rerun this program\n");
	return(-1);
  }

  if ((len = i2d_RSAPrivateKey(rsa, NULL)) == 0) {
	fprintf(stderr, "Error encoding private_key\n");
	ERR_print_errors_fp(stderr);
	return(-1);
  }
  buf = next = (unsigned char *) malloc(len);
  i2d_RSAPrivateKey(rsa, &next);
  strba64(buf, (unsigned int) len, private_key);

  if ((len = i2d_RSAPublicKey(rsa, NULL)) == 0) {
	fprintf(stderr, "Error encoding public_key\n");
	ERR_print_errors_fp(stderr);
	return(-1);
  }
  buf = next = (unsigned char *) malloc(len);
  i2d_RSAPublicKey(rsa, &next);
  strba64(buf, (unsigned int) len, public_key);

  RSA_free(rsa);
  return(0);
}

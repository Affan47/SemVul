check_bitlen_rsa(RSA *rsa, int ispub, unsigned int *pmagic)
	{
	int nbyte, hnbyte, bitlen;
	if (BN_num_bits(rsa->e) > 32)
		goto badkey;
	bitlen = BN_num_bits(rsa->n);
	nbyte = BN_num_bytes(rsa->n);
	hnbyte = (BN_num_bits(rsa->n) + 15) >> 4;
	if (ispub)
		{
		*pmagic = MS_RSA1MAGIC;
		return bitlen;
		}
	else
	{
		*pmagic = MS_RSA2MAGIC;


		if (BN_num_bytes(rsa->d) > nbyte)
			goto badkey;
		if ((BN_num_bytes(rsa->iqmp) > hnbyte)
			|| (BN_num_bytes(rsa->p) > hnbyte)
			|| (BN_num_bytes(rsa->q) > hnbyte)
			|| (BN_num_bytes(rsa->dmp1) > hnbyte)
			|| (BN_num_bytes(rsa->dmq1) > hnbyte))
			goto badkey;
	}
	return bitlen;
	badkey:
	PEMerr(PEM_F_CHECK_BITLEN_RSA, PEM_R_UNSUPPORTED_KEY_COMPONENTS);
	return 0;
	}

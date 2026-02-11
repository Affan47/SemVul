rc2_meth_to_magic(EVP_CIPHER_CTX *e)
	{
	int i;

	EVP_CIPHER_CTX_ctrl(e, EVP_CTRL_GET_RC2_KEY_BITS, 0, &i);
	if 	(i == 128) return(RC2_128_MAGIC);
	else if (i == 64)  return(RC2_64_MAGIC);
	else if (i == 40)  return(RC2_40_MAGIC);
	else return(0);
	}

bnrand(int pseudorand, BIGNUM *rnd, int bits, int top, int bottom)
	{
	unsigned char *buf=NULL;
	int ret=0,bit,bytes,mask;
	time_t tim;

	if (bits == 0)
		{
		BN_zero(rnd);
		return 1;
		}

	bytes=(bits+7)/8;
	bit=(bits-1)%8;
	mask=0xff<<(bit+1);

	buf=(unsigned char *)OPENSSL_malloc(bytes);
	if (buf == NULL)
		{
		BNerr(BN_F_BNRAND,ERR_R_MALLOC_FAILURE);
		goto err;
		}


	time(&tim);
	RAND_add(&tim,sizeof(tim),0.0);

	if (pseudorand)
		{
		if (RAND_pseudo_bytes(buf, bytes) == -1)
			goto err;
		}
	else
		{
		if (RAND_bytes(buf, bytes) <= 0)
			goto err;
		}

#if 1
	if (pseudorand == 2)
		{


		int i;
		unsigned char c;

		for (i = 0; i < bytes; i++)
			{
			RAND_pseudo_bytes(&c, 1);
			if (c >= 128 && i > 0)
				buf[i] = buf[i-1];
			else if (c < 42)
				buf[i] = 0;
			else if (c < 84)
				buf[i] = 255;
			}
		}
#endif

	if (top != -1)
		{
		if (top)
			{
			if (bit == 0)
				{
				buf[0]=1;
				buf[1]|=0x80;
				}
			else
				{
				buf[0]|=(3<<(bit-1));
				}
			}
		else
			{
			buf[0]|=(1<<bit);
			}
		}
	buf[0] &= ~mask;
	if (bottom)
		buf[bytes-1]|=1;
	if (!BN_bin2bn(buf,bytes,rnd)) goto err;
	ret=1;
err:
	if (buf != NULL)
		{
		OPENSSL_cleanse(buf,bytes);
		OPENSSL_free(buf);
		}
	bn_check_top(rnd);
	return(ret);
	}

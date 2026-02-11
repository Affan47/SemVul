setRSAFlags(RSA* pRSA)
	{
		if(pRSA==NULL)
			return;
		pRSA->flags|=RSA_FLAG_THREAD_SAFE;
		#ifdef RSA_FLAG_NO_BLINDING
			pRSA->flags|=RSA_FLAG_NO_BLINDING;
		#endif
#if OPENSSL_VERSION_NUMBER	> 0x0090707fL
		pRSA->flags|=RSA_FLAG_NO_EXP_CONSTTIME;
#endif
	}

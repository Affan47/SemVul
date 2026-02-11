verifyDER(UINT8* in, UINT32 inlen, const UINT8 * dsaSig, const UINT32 sigLen)
	{
		UINT8 dgst[SHA_DIGEST_LENGTH];
		UINT32 rc;

		if(m_pDSA==NULL||dsaSig==NULL)
			return E_UNKNOWN;
		SHA1(in,inlen,dgst);
		if((rc=DSA_verify(0, dgst, SHA_DIGEST_LENGTH, dsaSig, sigLen, m_pDSA))==1)
			return E_SUCCESS;
		else if(rc==0)
			return E_INVALID;
		return E_UNKNOWN;
	}

decrypt1CBCwithPKCS7(const UINT8* in,UINT8* out,UINT32* len)
	{
		if(in==NULL||out==NULL||len==NULL||*len==0)
			return E_UNKNOWN;
		AES_cbc_encrypt(in,out,*len,m_keyAES,m_iv1,AES_DECRYPT);

		UINT32 pad=out[*len-1];
		if(pad>16||pad>*len)
			return E_UNKNOWN;
		for(UINT32 i=*len-pad;i<*len-1;i++)
				if(out[i]!=pad)
					return E_UNKNOWN;
		*len-=pad;
		return E_SUCCESS;
	}

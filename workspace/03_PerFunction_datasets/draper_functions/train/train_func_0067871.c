Encrypt(char const* in, char* result, size_t n, int iMode)
{
	if(false==m_bKeyInit)
		throw runtime_error(sm_szErrorMsg1);

	if(0==n || n%m_blockSize!=0)
		throw runtime_error(sm_szErrorMsg2);
	int i;
	char const* pin;
	char* presult;
	if(CBC == iMode)
	{
		for(i=0,pin=in,presult=result; i<n/m_blockSize; i++)
		{
			Xor(m_chain, pin);
			EncryptBlock(m_chain, presult);
			memcpy(m_chain, presult, m_blockSize);
			pin += m_blockSize;
			presult += m_blockSize;
		}
	}
	else if(CFB == iMode)
	{
		for(i=0,pin=in,presult=result; i<n/m_blockSize; i++)
		{
			EncryptBlock(m_chain, presult);
			Xor(presult, pin);
			memcpy(m_chain, presult, m_blockSize);
			pin += m_blockSize;
			presult += m_blockSize;
		}
	}
	else
	{
		for(i=0,pin=in,presult=result; i<n/m_blockSize; i++)
		{
			EncryptBlock(pin, presult);
			pin += m_blockSize;
			presult += m_blockSize;
		}
	}
}

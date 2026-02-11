_TwoFish_CryptRawCBC(char *in,char *out,unsigned long len,bool decrypt,TWOFISH *tfdata)
{	unsigned long rl;

	rl=len;
	while(len>TwoFish_BLOCK_SIZE)
	{	_TwoFish_BlockCrypt((uint8_t *)in,(uint8_t *)out,TwoFish_BLOCK_SIZE,decrypt,tfdata);
		in+=TwoFish_BLOCK_SIZE;
		out+=TwoFish_BLOCK_SIZE;
		len-=TwoFish_BLOCK_SIZE;
	}
	if(len>0)
		_TwoFish_BlockCrypt((uint8_t *)in,(uint8_t *)out,len,decrypt,tfdata);
	if(tfdata->qBlockDefined && !tfdata->dontflush)
		_TwoFish_FlushOutput(tfdata->qBlockCrypt,TwoFish_BLOCK_SIZE,tfdata);

	return rl;
}

cca_rsa_pub_enc(int flen, const unsigned char *from,
			unsigned char *to, RSA *rsa,int padding)
	{
	long returnCode;
	long reasonCode;
	long lflen = flen;
	long exitDataLength = 0;
	unsigned char exitData[8];
	long ruleArrayLength = 1;
	unsigned char ruleArray[8] = "PKCS-1.2";
	long dataStructureLength = 0;
	unsigned char dataStructure[8];
	long outputLength = RSA_size(rsa);
	long keyTokenLength;
	unsigned char* keyToken = (unsigned char*)RSA_get_ex_data(rsa, hndidx);

	keyTokenLength = *(long*)keyToken;
	keyToken+=sizeof(long);

	pkaEncrypt(&returnCode, &reasonCode, &exitDataLength, exitData,
		&ruleArrayLength, ruleArray, &lflen, (unsigned char*)from,
		&dataStructureLength, dataStructure, &keyTokenLength,
		keyToken, &outputLength, to);

	if (returnCode || reasonCode)
		return -(returnCode << 16 | reasonCode);
	return outputLength;
	}

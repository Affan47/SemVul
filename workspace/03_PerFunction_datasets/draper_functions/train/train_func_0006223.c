Rijndael_padEncrypt(const uint8_t *input, int inputOctets, uint8_t *outBuffer)
{
	int i, numBlocks, padLen;
	uint8_t block[16], *iv;

	if(m_state != Valid)return RIJNDAEL_NOT_INITIALIZED;
	if(m_direction != Encrypt)return RIJNDAEL_NOT_INITIALIZED;

	if(input == 0 || inputOctets <= 0)return 0;

	numBlocks = inputOctets/16;

	switch(m_mode)
	{
		case ECB:
			for(i = numBlocks; i > 0; i--)
			{
				encrypt(input, outBuffer);
				input += 16;
				outBuffer += 16;
			}
			padLen = 16 - (inputOctets - 16*numBlocks);

			memcpy(block, input, 16 - padLen);
			memset(block + 16 - padLen, padLen, padLen);
			encrypt(block,outBuffer);
		break;
		case CBC:
			iv = m_initVector;
			for(i = numBlocks; i > 0; i--)
			{
				((uint32_t*)block)[0] = ((uint32_t*)input)[0] ^ ((uint32_t*)iv)[0];
				((uint32_t*)block)[1] = ((uint32_t*)input)[1] ^ ((uint32_t*)iv)[1];
				((uint32_t*)block)[2] = ((uint32_t*)input)[2] ^ ((uint32_t*)iv)[2];
				((uint32_t*)block)[3] = ((uint32_t*)input)[3] ^ ((uint32_t*)iv)[3];
				encrypt(block, outBuffer);
				iv = outBuffer;
				input += 16;
				outBuffer += 16;
			}
			padLen = 16 - (inputOctets - 16*numBlocks);

			for (i = 0; i < 16 - padLen; i++) {
				block[i] = input[i] ^ iv[i];
			}
			for (i = 16 - padLen; i < 16; i++) {
				block[i] = (uint8_t)padLen ^ iv[i];
			}
			encrypt(block,outBuffer);
		break;
		default:
			return -1;
		break;
	}

	return 16*(numBlocks + 1);
}

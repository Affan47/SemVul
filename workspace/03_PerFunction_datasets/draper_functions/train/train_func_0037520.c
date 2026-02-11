PCMACDec(Chunk PCMACTag, unsigned char *m, unsigned long long *mlen,
		const unsigned char *c, unsigned long long clen, unsigned char *nonce,
		unsigned char *PCMACKey)
{
	Byte finalKey[kSIZE];
	int i, j;
	int isValid = -1;
	int test = 0;
	unsigned long long numOfChunks = 0;
	Chunk r;
	AESArguments *input;
	AES_KEY key;
	numOfChunks = (unsigned long long) clen / SIZE;

	input = (struct AES_Arguments*) malloc(
			(numOfChunks + 1) * sizeof(struct AES_Arguments));

	SetupForDec(input, c, numOfChunks);

	for (j = 0; j < numOfChunks; j++)
	{
		Increment(nonce);

		for (i = 0; i < SIZE; i++)
		{
			for (i = 0; i < kSIZE; i++)
				input[j].nonce[i] = nonce[i];
		}

	}
	for (j = 0; j < numOfChunks; j++)
	{
		XORKey(input[j].nonce, PCMACKey, finalKey);

		AES_set_decrypt_key(finalKey, 192, &key);
		AES_decrypt(input[j].cipherText, input[j].plainText, &key);
	}

	for (j = 0; j < numOfChunks; j++)
		for (i = 0; i < SIZE; i++)
			m[(j * SIZE) + i] = input[j + 1].plainText[i];

	*mlen = clen - CRYPTO_ABYTES + SIZE;

	if (m[*mlen] == EOT)
		isValid = 0;

	if (isValid != 0)
	{
		free(input);
		return isValid;
	}

	memcpy(r, input[0].plainText, SIZE);

	TagGeneration(m, r, PCMACTag, numOfChunks);

	free(input);

	return isValid;
}

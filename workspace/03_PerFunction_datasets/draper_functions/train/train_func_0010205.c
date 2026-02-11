Sign(Chunk prime, Chunk key, const Byte *m, int length, Chunk Tag)
{
	int i;
	Chunk mRes;
	Byte *result, *mApp;
	if (length < 16)
	{
		result = (Byte*) malloc((SIZE * 2) * sizeof(Byte));
		mApp = (Byte*) malloc((SIZE * 2) * sizeof(Byte));
		memset(mApp, 0, SIZE * 2);

	}
	else
	{
		result = (Byte*) malloc((length * 2) * sizeof(Byte));
		mApp = (Byte*) malloc((length * 2) * sizeof(Byte));
		memset(mApp, 0, length * 2);
	}

	AppendOne(m, mApp, length);

	Reduce(mApp, prime, mRes, length);

	InterleavedModularMultiplication(key, mRes, prime, result);

	for (i = 0; i < SIZE; ++i)
		Tag[i] = result[SIZE - 1 - i];

	free(result);
	free(mApp);
}

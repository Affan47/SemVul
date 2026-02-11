FABMemoryPoolRandomTester()
{

	struct timeval startTime, endTime;
	unsigned long long costTime = 0ULL;


	char **pStrings = (char **)malloc(sizeof(char *) * TEST_MALLOC_TIMES);
	for (int i=0; i<TEST_MALLOC_TIMES; ++i)
	{
		pStrings[i] = NULL;
	}

	int aRandom[TEST_MALLOC_TIMES];
	srand((unsigned int)time(NULL) + rand());
	for (int i=0; i<TEST_MALLOC_TIMES; ++i)
	{
		aRandom[i] = rand() % MALLOC_MAX_LEN;
		srand(aRandom[i]);
	}


	PrintLog("Now testing memory pool Malloc/Free, FAB memory pool.");
	PrintLog("Note: This test is just for function test, time test is meaningless.");
	gettimeofday(&startTime, NULL);

	MemoryPool_t *pPool = CreateMemoryPool(MALLOC_MAX_LEN, FIRST_CHUNK_BLOCKS, GROW_CHUNK_BLOCKS);
	for (int i=0; i<TEST_RETRY_TIMES; ++i)
	{
		for (int j=0; j<TEST_MALLOC_TIMES; ++j)
		{
			if (aRandom[j] % 2)
			{
				pStrings[j] = (char *)Malloc(pPool);
				*pStrings[j] = '\0';
			}
		}
		for (int j=0; j<TEST_MALLOC_TIMES; ++j)
		{
			if ((aRandom[j] % 3) && pStrings[j])
			{
				Free(pPool, pStrings[j]);
				pStrings[j] = NULL;
			}
		}
	}
	DestroyMemoryPool(&pPool);

	gettimeofday(&endTime, NULL);
	costTime = 1000 * 1000 * (endTime.tv_sec - startTime.tv_sec) + endTime.tv_usec - startTime.tv_usec;
	printf("Memory pool Malloc/Free tested, malloc and free %d strings for %d times, cost %llu us.\n",
			TEST_MALLOC_TIMES, TEST_RETRY_TIMES, costTime);

	free(pStrings);
	return 0;
}

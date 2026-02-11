SystemDefaultAllocatorTest_FixedLen()
{

	struct timeval startTime, endTime;
	unsigned long long costTime = 0ULL;

	char **pStrings = (char **)malloc(sizeof(char *) * TEST_MALLOC_TIMES);


	PrintLog("Now testing system default malloc/free, fixed length.");
	gettimeofday(&startTime, NULL);
	for (int i=0; i<TEST_RETRY_TIMES; ++i)
	{
		for (int j=0; j<TEST_MALLOC_TIMES; ++j)
		{
			pStrings[j] = (char *)malloc(sizeof(char) * MALLOC_MAX_LEN);
			*pStrings[j] = '\0';

			free(pStrings[j]);
		}
	}
	gettimeofday(&endTime, NULL);
	costTime = 1000 * 1000 * (endTime.tv_sec - startTime.tv_sec) + endTime.tv_usec - startTime.tv_usec;
	printf("System default malloc/free tested, malloc and free %d strings for %d times, cost %llu us.\n",
			TEST_MALLOC_TIMES, TEST_RETRY_TIMES, costTime);

	free(pStrings);
	return 0;
}

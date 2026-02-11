main(int argc, char **argv)
{

	if(argc < 2 || argc > 3)
	{
		return EXIT_FAILURE;
	}

	int dryRun = 0;
	if(argc == 3)
	{
		if(strcmp("--dry-run", argv[2]) == 0)
		{
			dryRun = 1;
		}
		else
		{
			return EXIT_FAILURE;
		}
	}


	char* buffer = readFile(argv[1]);
	if(buffer == NULL)
	{
		return EXIT_FAILURE;
	}


	int lineCount = 0;
	char** lines = splitToLines(buffer, &lineCount);
	if(lines == NULL)
	{
		return EXIT_FAILURE;
	}


	size_t resultBufferSize = BUFFER_GRANULARITY;
	size_t resultBufferUsed = 0;

	char* resultBuffer = growOrKill(NULL, resultBufferSize * sizeof(char));
	resultBuffer[0] = '\0';

	if(resultBuffer == NULL)
	{
		free(lines);
		free(buffer);
		return EXIT_FAILURE;
	}

	int i;

	if(dryRun)
	{
		for(i = 0; i < lineCount; i++);
	}
	else
	{
		for(i = 0; i < lineCount; i++)
		{
			size_t lineLength = strlen(lines[i]);


			while(resultBufferUsed + lineLength + 1>= resultBufferSize)
			{
				resultBufferSize += BUFFER_GRANULARITY;
				resultBuffer = growOrKill(resultBuffer, resultBufferSize * sizeof(char));
				if(resultBuffer == NULL)
				{
					free(lines);
					free(buffer);
					return EXIT_FAILURE;
				}
			}

			strcat(resultBuffer, lines[i]);
			strcat(resultBuffer, "\n");
			resultBufferUsed += lineLength + 1;


		}
	}


	free(resultBuffer);


	free(lines);
	free(buffer);
	return EXIT_SUCCESS;
}

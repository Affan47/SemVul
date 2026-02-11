UArray_readLineFromCStream_(UArray *self, FILE *stream)
{
	int readSomething = 0;

	if(self->itemSize == 1)
	{
		char *s = (char *)io_calloc(1, CHUNK_SIZE);

		while (fgets(s, CHUNK_SIZE, stream) != NULL)
		{
			long i;
			long start = strlen(s) - 1;


			for (i = start; (i >= 0) && ((s[i] == '\n') || (s[i] == '\r')) ; s[i--] = '\0') ;

			readSomething = 1;

			if (*s)
			{
				UArray_appendCString_(self, s);
			}


			if (i < start) {
				break;
			}
		}

		io_free(s);
	}

	return readSomething;
}

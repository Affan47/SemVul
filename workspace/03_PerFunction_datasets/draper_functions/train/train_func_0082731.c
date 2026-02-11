readLogFile(char *filename, int startEntry, int endEntry)
{
	char line[BIG_LINE];
	int entryIndex = 0;

	FILE *f = fopen(filename, "r");

	if(f != NULL)
	{
		while(fgets(line, BIG_LINE, f))
		{
			if(strstr(line, "format=") == NULL)
			{
				if((entryIndex >= startEntry) && (entryIndex <= endEntry))
					fprintf(stdout, "%s", line);
				entryIndex++;
			}
		}
		fclose(f);
		return 0;
	}
	return 1;
}

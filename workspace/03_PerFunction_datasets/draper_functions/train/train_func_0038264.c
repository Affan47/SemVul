setCurrentDirectory (void)
{
#ifndef AMIGA
	char* buf;
#endif
	if (CurrentDirectory == NULL)
		CurrentDirectory = xMalloc ((size_t) (PATH_MAX + 1), char);
#ifdef AMIGA
	strcpy (CurrentDirectory, ".");
#else
	buf = getcwd (CurrentDirectory, PATH_MAX);
	if (buf == NULL)
		perror ("");
#endif
	if (CurrentDirectory [strlen (CurrentDirectory) - (size_t) 1] !=
			PATH_SEPARATOR)
	{
		sprintf (CurrentDirectory + strlen (CurrentDirectory), "%c",
				OUTPUT_PATH_SEPARATOR);
	}
}

show_bindir(bool all)
{
	char		path[MAXPGPATH];
	char	   *lastsep;

	if (all)
		printf("BINDIR = ");

	strcpy(path, mypath);
	lastsep = strrchr(path, '/');

	if (lastsep)
		*lastsep = '\0';

	cleanup_path(path);
	printf("%s\n", path);
}

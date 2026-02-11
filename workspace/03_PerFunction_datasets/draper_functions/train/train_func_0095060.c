process_psqlrc_file(char *filename)
{
	char	   *psqlrc;

#if defined(WIN32) && (!defined(__MINGW32__))
#define R_OK 4
#endif

	psqlrc = pg_malloc(strlen(filename) + 1 + strlen(PG_VERSION) + 1);
	sprintf(psqlrc, "%s-%s", filename, PG_VERSION);

	if (access(psqlrc, R_OK) == 0)
		(void) process_file(psqlrc, false);
	else if (access(filename, R_OK) == 0)
		(void) process_file(filename, false);
	free(psqlrc);
}

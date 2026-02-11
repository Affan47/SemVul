statcurnew(const char *dir, time_t *maxtimestamp)
{
char	*p=(char *)malloc(strlen(dir)+5);
struct	stat	stat_buf;

	if (!p)	return (-1);
	strcat(strcpy(p, dir), "/cur");
	if ( stat(p, &stat_buf) == 0 && stat_buf.st_mtime > *maxtimestamp)
		*maxtimestamp=stat_buf.st_mtime;
	strcat(strcpy(p, dir), "/new");
	if ( stat(p, &stat_buf) == 0 && stat_buf.st_mtime > *maxtimestamp)
		*maxtimestamp=stat_buf.st_mtime;
	free(p);
	return (0);
}

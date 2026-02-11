mstrcpy(char **dest, char *src)
{
	if(*dest != NULL)
		xfree(*dest);

	if(src == NULL)
	{
		Log_write(LOG_DEBUG,"*","*** Attempting to mstrcpy with NULL src.");
		return;
	}
	*dest = (char *)xmalloc(strlen(src)+1);
	strcpy(*dest,src);
}

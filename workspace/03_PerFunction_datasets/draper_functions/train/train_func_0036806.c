prepage(char *buffer,long long reclen)
#else
void
prepage(buffer, reclen)
char *buffer;
long long reclen;
#endif
{
	char *where;
	long long i;
	where=(char *)buffer;
	for(i=0;i<(reclen/cache_line_size);i++)
	{
		*(where)=PATTERN;
		where+=cache_line_size;
	}
}

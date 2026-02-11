purgeit(char *buffer,long long reclen)
#else
void
purgeit(buffer,reclen)
char *buffer;
long long reclen;
#endif
{
	char *where;
	long rsize;
	long tsize;
	VOLATILE long long x[200];
	long i,cache_lines_per_rec;
	long cache_lines_per_cache;
	tsize = 200;
	cache_lines_per_rec = (long)(reclen/cache_line_size);
	cache_lines_per_cache = (long)(cache_size/cache_line_size);
	rsize = (long)l_min((long long)cache_lines_per_rec,(long long)cache_lines_per_cache);
#ifdef _64BIT_ARCH_
	where=(char *)pbuffer + ((unsigned long long)buffer & (cache_size-1));
#else
	where=(char *)pbuffer + ((long)buffer & ((long)cache_size-1));
#endif
	for(i=0;i<(rsize);i++)
	{
		x[i%tsize]=*(where);
		where+=cache_line_size;

	}
}

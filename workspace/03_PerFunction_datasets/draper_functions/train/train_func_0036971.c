Mono_Posix_FromMmapFlags (int x, int *r)
{
	*r = 0;
	if ((x & Mono_Posix_MmapFlags_MAP_ANON) == Mono_Posix_MmapFlags_MAP_ANON)
#ifdef MAP_ANON
		*r |= MAP_ANON;
#else
		{errno = EINVAL; return -1;}
#endif
	if ((x & Mono_Posix_MmapFlags_MAP_ANONYMOUS) == Mono_Posix_MmapFlags_MAP_ANONYMOUS)
#ifdef MAP_ANONYMOUS
		*r |= MAP_ANONYMOUS;
#else
		{errno = EINVAL; return -1;}
#endif
	if ((x & Mono_Posix_MmapFlags_MAP_DENYWRITE) == Mono_Posix_MmapFlags_MAP_DENYWRITE)
#ifdef MAP_DENYWRITE
		*r |= MAP_DENYWRITE;
#else
		{errno = EINVAL; return -1;}
#endif
	if ((x & Mono_Posix_MmapFlags_MAP_EXECUTABLE) == Mono_Posix_MmapFlags_MAP_EXECUTABLE)
#ifdef MAP_EXECUTABLE
		*r |= MAP_EXECUTABLE;
#else
		{errno = EINVAL; return -1;}
#endif
	if ((x & Mono_Posix_MmapFlags_MAP_FILE) == Mono_Posix_MmapFlags_MAP_FILE)
#ifdef MAP_FILE
		*r |= MAP_FILE;
#else
		{errno = EINVAL; return -1;}
#endif
	if ((x & Mono_Posix_MmapFlags_MAP_FIXED) == Mono_Posix_MmapFlags_MAP_FIXED)
#ifdef MAP_FIXED
		*r |= MAP_FIXED;
#else
		{errno = EINVAL; return -1;}
#endif
	if ((x & Mono_Posix_MmapFlags_MAP_GROWSDOWN) == Mono_Posix_MmapFlags_MAP_GROWSDOWN)
#ifdef MAP_GROWSDOWN
		*r |= MAP_GROWSDOWN;
#else
		{errno = EINVAL; return -1;}
#endif
	if ((x & Mono_Posix_MmapFlags_MAP_LOCKED) == Mono_Posix_MmapFlags_MAP_LOCKED)
#ifdef MAP_LOCKED
		*r |= MAP_LOCKED;
#else
		{errno = EINVAL; return -1;}
#endif
	if ((x & Mono_Posix_MmapFlags_MAP_NONBLOCK) == Mono_Posix_MmapFlags_MAP_NONBLOCK)
#ifdef MAP_NONBLOCK
		*r |= MAP_NONBLOCK;
#else
		{errno = EINVAL; return -1;}
#endif
	if ((x & Mono_Posix_MmapFlags_MAP_NORESERVE) == Mono_Posix_MmapFlags_MAP_NORESERVE)
#ifdef MAP_NORESERVE
		*r |= MAP_NORESERVE;
#else
		{errno = EINVAL; return -1;}
#endif
	if ((x & Mono_Posix_MmapFlags_MAP_POPULATE) == Mono_Posix_MmapFlags_MAP_POPULATE)
#ifdef MAP_POPULATE
		*r |= MAP_POPULATE;
#else
		{errno = EINVAL; return -1;}
#endif
	if ((x & Mono_Posix_MmapFlags_MAP_PRIVATE) == Mono_Posix_MmapFlags_MAP_PRIVATE)
#ifdef MAP_PRIVATE
		*r |= MAP_PRIVATE;
#else
		{errno = EINVAL; return -1;}
#endif
	if ((x & Mono_Posix_MmapFlags_MAP_SHARED) == Mono_Posix_MmapFlags_MAP_SHARED)
#ifdef MAP_SHARED
		*r |= MAP_SHARED;
#else
		{errno = EINVAL; return -1;}
#endif
	if ((x & Mono_Posix_MmapFlags_MAP_TYPE) == Mono_Posix_MmapFlags_MAP_TYPE)
#ifdef MAP_TYPE
		*r |= MAP_TYPE;
#else
		{errno = EINVAL; return -1;}
#endif
	if (x == 0)
		return 0;
	return 0;
}

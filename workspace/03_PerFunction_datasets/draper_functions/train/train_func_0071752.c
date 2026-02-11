_init_mem_properties(void)
{
#ifndef __WINNT__
	struct rlimit rlp;
#if defined(__LINUX__)
	if (prctl(PR_SET_DUMPABLE, 0, 0, 0, 0)) {
		fprintf(stderr, "unable to disable core dumps\n");
		exit(-1);
	}
#endif
	rlp.rlim_cur = 0;
	rlp.rlim_max = 0;
	if (setrlimit(RLIMIT_CORE, &rlp)) {
		fprintf(stderr, "unable to disable core dumps\n");
		exit(-1);
	}
	_pagesize = sysconf(_SC_PAGESIZE);
	if (_pagesize == -1 || !_pagesize) {
		fprintf(stderr, "unable to determine pagesize\n");
		exit(-1);
	}
#if defined(__LINUX__)
	if (sysconf(_SC_MEMLOCK_RANGE) == -1) {
		fprintf(stderr, "no memlocking available\n");
		exit(-1);
	}
#endif
	if (getrlimit(RLIMIT_MEMLOCK, &rlp)) {
		fprintf(stderr, "can't get memlock limits\n");
		exit(-1);
	}
	_max_locked_mem = rlp.rlim_cur;
#else
	size_t _min_locked_mem;

	if (!GetProcessWorkingSetSize(GetCurrentProcess(),
	&_min_locked_mem, &_max_locked_mem)) {
		fprintf(stderr, "can't get memlock limits\n");
		exit(-1);
	}

	_max_locked_mem = _min_locked_mem;

	SYSTEM_INFO si;
        GetSystemInfo(&si);
        _pagesize = si.dwPageSize;


#endif
}

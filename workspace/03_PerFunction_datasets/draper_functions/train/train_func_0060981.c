my_getrusage(struct rusage *a)
{
      getrusage(RUSAGE_SELF, a);

#     if defined(LINUX)
      {
	    FILE *statm;
	    unsigned siz, rss, shd;
	    long page_size = sysconf(_SC_PAGESIZE);
	    if (page_size==-1) page_size=0;
	    statm = fopen("/proc/self/statm", "r");
	    if (!statm) {
		  perror("/proc/self/statm");
		  return;
	    }
	    if (3<=fscanf(statm, "%u%u%u", &siz, &rss, &shd)) {
		  a->ru_maxrss = page_size * siz;
		  a->ru_idrss  = page_size * rss;
		  a->ru_ixrss  = page_size * shd;
	    }
	    fclose(statm);
      }
#     endif
}

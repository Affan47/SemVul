es_set_nthreads_string(const char *str)
{
  bool doDetect = strcasecmp(str, "detect") == 0;
  if(strcasecmp(str, "env") == 0 || doDetect) {
      const char *env = getenv("OMP_NUM_THREADS");
      int defThreads = 1;
      if ( !(env && (defThreads=atoi(env)) > 0) ) {
	if(doDetect) {
	  FILE *f = fopen("/proc/cpuinfo", "rt");
	  if(f) {
	    char line[256];
	    defThreads = 0;
	    while(fgets(line, sizeof(line), f))
	      if(strncmp(line, "processor", 9) == 0)
		defThreads++;
	    fclose(f);


	    if(defThreads == 0)
	      defThreads = 1;
	  }
	}
      }
      es_set_nthreads(defThreads);
      return 0;
  } else
    return -1;
}

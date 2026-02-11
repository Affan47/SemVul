calc_nstrips(flam3_frame *spec) {
  double mem_required;
  double mem_available;
  int nstrips,ninc;
  char *testmalloc;
#ifdef WIN32
  MEMORYSTATUS stat;
  stat.dwLength = sizeof(stat);
  GlobalMemoryStatus(&stat);
  mem_available = (double)stat.dwTotalPhys;


#elif defined(_SC_PHYS_PAGES) && defined(_SC_PAGESIZE)
  mem_available =
      (double)sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE);
#elif defined __APPLE__
#ifdef __LP64__
long physmem;
size_t len = sizeof(physmem);
static int mib[2] = { CTL_HW, HW_MEMSIZE };
#else
unsigned int physmem;
size_t len = sizeof(physmem);
static int mib[2] = { CTL_HW, HW_PHYSMEM };
#endif
if (sysctl(mib, 2, &physmem, &len, NULL, 0) == 0 && len == sizeof(physmem)) {
   mem_available = (double )physmem;
} else {
   fprintf(stderr, "warning: unable to determine physical memory.n");
   mem_available = 2e9;
}
#else
  fprintf(stderr, "warning: unable to determine physical memory.\n");
  mem_available = 2e9;
#endif
#if 0
  fprintf(stderr,"available phyical memory is %lu\n",
	  (unsigned long)mem_available);
#endif
  mem_available *= 0.8;
  if (getenv("use_mem")) {
      mem_available = atof(getenv("use_mem"));
  }
  mem_required = flam3_render_memory_required(spec);
  if (mem_available >= mem_required) return 1;
  nstrips = (int) ceil(mem_required / mem_available);

if (0) {

  ninc=-1;
  testmalloc = NULL;
  while(NULL==testmalloc && ninc<3) {
     ninc++;
	  testmalloc = (char *)malloc((int)ceil(mem_required / (nstrips+ninc)));
  }
  if (NULL==testmalloc) {
     fprintf(stderr,"Unable to allocate memory for render.  Please close some running programs and try to render again.\n");
     exit(1);
  } else {
     free(testmalloc);
     nstrips = nstrips + ninc;
  }
}

  return nstrips;
}

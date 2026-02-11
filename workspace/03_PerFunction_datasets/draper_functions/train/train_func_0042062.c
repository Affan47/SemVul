openFiles()
{
  final = NULL;
  speedfile = NULL;
  stream = NULL;
  datafile = NULL;
  ipedfile = NULL;
  outfile = NULL;

  datafile = fopen("datafile.dat", "r");
  if (datafile == NULL)
    exit(FileNotFound);
  ipedfile = fopen("ipedfile.dat", "r");
  if (ipedfile == NULL)
    exit(FileNotFound);
#if ALLELE_SPEED
  speedfile = fopen("newspeedfile.dat", "r");
#else
  speedfile = fopen("speedfile.dat", "r");
#endif
  if (speedfile == NULL)
    exit(FileNotFound);

#if PARALLEL
#if defined(LESSMEMORY)
  if (PRECOMPUTE)
    Tmk_errexit("Cannot have LESSMEMORY defined and PRECOMPUTE set to 1\n");
#endif


     if (Tmk_proc_id ==0) {
#endif
#ifdef vms
    outfile = fopen("outfile.dat", "w", "ctx=rec","shr=get,put,upd" ) ;
#else
    outfile = fopen("outfile.dat", "w");
#endif
    if (outfile == NULL)
      exit(FileNotFound);
    if (dostream) {
#ifdef vms
      stream = fopen("stream.dat", "w", "ctx=rec","shr=get,put,upd" ) ;
#else
      stream = fopen("stream.dat", "w");
#endif
      if (stream == NULL)
	exit(FileNotFound);
    }
#if defined(ILINK)
#ifdef vms
    final = fopen("final.dat", "w", "ctx=rec","shr=get,put,upd" ) ;
#else
    final = fopen("final.dat", "w");
#endif
    if (final == NULL)
      exit(FileNotFound);
#endif
#if PARALLEL
  }
#endif
}

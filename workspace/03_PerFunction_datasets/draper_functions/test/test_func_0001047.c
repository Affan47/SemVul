version(void)
{
  int   filetypes[] = {FILETYPE_SRV, FILETYPE_EXT, FILETYPE_IEG, FILETYPE_GRB, FILETYPE_GRB2, FILETYPE_NC, FILETYPE_NC2, FILETYPE_NC4, FILETYPE_NC4C};
  char *typenames[] = {        "srv",        "ext",        "ieg",        "grb",        "grb2",        "nc",        "nc2",        "nc4",        "nc4c"};

  fprintf(stderr, "CDI version 1.8\n");
#if defined (COMPILER)
  fprintf(stderr, "Compiler: %s\n", COMPILER);
#endif
#if defined (COMP_VERSION)
  fprintf(stderr, " version: %s\n", COMP_VERSION);
#endif
#if defined (USER_NAME) && defined(HOST_NAME) && defined(SYSTEM_TYPE)
  fprintf(stderr, "Compiled: by %s on %s (%s) %s %s\n",
	  USER_NAME, HOST_NAME, SYSTEM_TYPE, __DATE__, __TIME__);
#endif

  fprintf(stderr, "filetype: ");
  for ( size_t i = 0; i < sizeof(filetypes)/sizeof(int); ++i )
    if ( cdiHaveFiletype(filetypes[i]) ) fprintf(stderr, "%s ", typenames[i]);
  fprintf(stderr, "\n");

  fprintf(stderr, "    with:");
#if defined (HAVE_LIBPTHREAD)
  fprintf(stderr, " PTHREADS");
#endif
#if defined (_OPENMP)
  fprintf(stderr, " OpenMP");
#endif
#if  defined  (HAVE_NETCDF4)
  fprintf(stderr, " NC4");
#endif
#if  defined  (HAVE_LIBNC_DAP)
  fprintf(stderr, " OPeNDAP");
#endif
#if defined (HAVE_LIBSZ)
  fprintf(stderr, " SZ");
#endif
#if defined (HAVE_LIBZ)
  fprintf(stderr, " Z");
#endif
#if defined (HAVE_LIBJASPER)
  fprintf(stderr, " JASPER");
#endif
#if defined (HAVE_LIBPROJ)
  fprintf(stderr, " PROJ.4");
#endif
#if defined (HAVE_LIBDRMAA)
  fprintf(stderr, " DRMAA");
#endif
#if defined (HAVE_LIBCURL)
  fprintf(stderr, " CURL");
#endif
  fprintf(stderr, "\n");
  cdiPrintVersion();
  fprintf(stderr, "\n");


}

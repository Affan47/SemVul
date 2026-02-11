initial_breakers()
{
  boolean *islooped;
  int i;
  FILE *lpedfile;

  pedfile = NULL;
  datafile = NULL;
#if LOOPSPEED
  unlink(LOOPFILE_NAME);
  loopfile = NULL;
#endif
#if LOOP_BREAKERS
  initunknown(OLD);
  readloci();
  gapsinIds = FALSE;
  totalNumPed = foundped();
  if (gapsinIds) {
    strcpy(pedfilename,"upedfile.dat");
    adjustIds();
  }
  else
    strcpy(pedfilename,"pedfile.dat");
  islooped = (boolean *) malloc(totalNumPed * sizeof(boolean));
  for(i = 0; i < totalNumPed; i++)
    islooped[i] = FALSE;
  if (pedfile != NULL) {
    fclose(pedfile);
    pedfile = NULL;
  }
  detectLoopedPedigrees(islooped);
  lpedfile = fopen(LPEDFILE_NAME, "w");
  if (NULL == lpedfile)
      exit(FileNotFound);
  loopbreakers2(lpedfile);
  if (datafile != NULL) {
    fclose(datafile);
    datafile = NULL;
  }
  if (pedfile != NULL) {
    fclose(pedfile);
    pedfile = NULL;
  }
  if (lpedfile != NULL) {
    fclose(lpedfile);
    lpedfile = NULL;
  }
#else
fprintf(stderr,"Cannot use unknown -l with LOOP_BREAKERS set to 0\n");
exit(EXIT_FAILURE);
#endif
}

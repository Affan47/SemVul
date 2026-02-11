Access_allocated (size_t *len, double *seconds, char *filename, size_t eltsize) {
  void *memory;
  FILE *fp;
  Stopwatch_T stopwatch;
  unsigned int value;
  void *p;
  int i;

  *len = (size_t) Access_filesize(filename);

  if ((fp = FOPEN_READ_BINARY(filename)) == NULL) {
    fprintf(stderr,"Error: can't open file %s with fopen\n",filename);
    exit(9);
  }

  Stopwatch_start(stopwatch = Stopwatch_new());
  memory = (void *) MALLOC(*len);
  FREAD_UINTS(memory,(*len)/eltsize,fp);
  fclose(fp);

#ifndef WORDS_BIGENDIAN
  value = first_nonzero(&i,filename);
  if (i >= 0 && ((unsigned int *) memory)[i] != value) {
    fprintf(stderr,"single fread command failed (observed on Macs with -B 3 or greater on large genomes)...reading file in smaller batches...");
    fp = FOPEN_READ_BINARY(filename);

    for (i = 0; i < (int) ((*len)/eltsize); i += FREAD_BATCH) {
      p = (void *) &(((unsigned int *) memory)[i]);
      fread(p,sizeof(unsigned int),FREAD_BATCH,fp);
    }

    if (i < (int) (*len)/eltsize) {
      p = (void *) &(((unsigned int *) memory)[i]);
      fread(p,sizeof(unsigned int),(*len)/eltsize - i,fp);
    }

    fclose(fp);
  }
#endif


  *seconds = Stopwatch_stop(stopwatch);
  Stopwatch_free(&stopwatch);

  return memory;
}

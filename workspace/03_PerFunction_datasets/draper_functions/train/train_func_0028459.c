getmoredata(Logfile *lf, char *start, size_t length) {
#ifndef LINE_PARSER
  int bze;
  void* unusedPtr;
  char* unusedData;
  int unusedCount;
#endif
  int n;

  switch (lf->type) {
  case LF_NORMAL:
  case LF_PIPE:
    n = fread((void *)start, 1, length, (FILE *)(lf->file));
    break;
#ifndef LINE_PARSER
  case LF_GZIP:
    n = gzread((gzFile)(lf->file), (void *)start, length);
    if (n < 0)
      n = 0;
    break;
  case LF_ZIPMEMBER:
    n = unzReadCurrentFile((unzFile)(lf->file), (void *)start, length);
    if (n < 0)
      n = 0;
    break;
  case LF_BZ2:
    n = 0;


    while (n < length) {
      n = n + BZ2_bzRead(&bze, (BZFILE *)(lf->file2), (void *)start + n, length - n);

      if (bze != BZ_OK && bze != BZ_STREAM_END) {
        n = 0;
        break;
      }

      if (bze == BZ_STREAM_END) {


        BZ2_bzReadGetUnused(&bze, (BZFILE *)(lf->file2), &unusedPtr, &unusedCount);
        if (bze != BZ_OK) {
          n = 0;
          break;
        }

        if (unusedCount == 0 && feof((FILE *)(lf->file))) {
          break;
        }


        unusedData = malloc(unusedCount);
        memcpy(unusedData, unusedPtr, unusedCount);


        BZ2_bzReadClose(&bze, (BZFILE *)(lf->file2));
        if (bze != BZ_OK) {
          n = 0;
          break;
        }


        lf->file2 = (void *)BZ2_bzReadOpen(&bze, (FILE *)(lf->file),
                  0, 0, unusedData, unusedCount);
        if (bze != BZ_OK || (BZFILE *)(lf->file2)==NULL) {
          n = 0;
          break;
        }


        free(unusedData);
      }
    }
    break;
#endif
  default:
    n = 0;
  }
  block_end = start + n;
  block_bell = block_end - BLOCK_EPSILON;


  if (block_end == start)
    return(EOF);
  return(OK);
}

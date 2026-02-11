_nrrdEncodingRaw_write(FILE *file, const void *data, size_t elementNum,
                       const Nrrd *nrrd, NrrdIoState *nio) {
  static const char me[]="_nrrdEncodingRaw_write";
  int fd, dio;
  size_t ret, bsize;
  const char *data_c;
  size_t elementSize, maxChunkSize, remainderValue, chunkSize;
  size_t retTmp;
  char stmp[3][AIR_STRLEN_SMALL];

  bsize = nrrdElementSize(nrrd)*elementNum;
  if (nio->format->usesDIO) {
    fd = fileno(file);
    dio = airDioTest(fd, data, bsize);
  } else {
    fd = -1;
    dio = airNoDio_format;
  }
  if (airNoDio_okay == dio) {
    if (2 <= nrrdStateVerboseIO) {
      fprintf(stderr, "with direct I/O ... ");
    }
    ret = airDioWrite(fd, data, bsize);
    if (ret != bsize) {
      biffAddf(NRRD, "%s: airDioWrite wrote only %s of %s bytes "
               "(%g%% of expected)", me,
               airSprintSize_t(stmp[0], ret),
               airSprintSize_t(stmp[1], bsize),
               100.0*AIR_CAST(double, ret)/AIR_CAST(double, bsize));
      return 1;
    }
  } else {
    if (2 <= nrrdStateVerboseIO) {
      if (AIR_DIO && nio->format->usesDIO) {
        fprintf(stderr, "with fread(), not DIO: %s ...", airNoDioErr(dio));
      }
    }


    ret = 0;
    data_c = AIR_CAST(const char *, data);
    elementSize = nrrdElementSize(nrrd);
    maxChunkSize = 1024 * 1024 * 1024 / elementSize;
    while(ret < elementNum) {
      remainderValue = elementNum-ret;
      if (remainderValue < maxChunkSize) {
        chunkSize = remainderValue;
      } else {
        chunkSize = maxChunkSize;
      }
      retTmp =
        fwrite(&(data_c[ret*elementSize]), elementSize, chunkSize, file);
      ret += retTmp;
      if (retTmp != chunkSize) {
        biffAddf(NRRD, "%s: fwrite wrote only %s %s-sized things, not %s "
                 "(%g%% of expected)", me,
                 airSprintSize_t(stmp[0], ret),
                 airSprintSize_t(stmp[1], nrrdElementSize(nrrd)),
                 airSprintSize_t(stmp[2], elementNum),
                 100.0*AIR_CAST(double, ret)/AIR_CAST(double, elementNum));
        return 1;
      }
    }

    fflush(file);


  }
  return 0;
}

_nrrdEncodingHex_write(FILE *file, const void *_data, size_t elNum,
                       const Nrrd *nrrd, NrrdIoState *nio) {

  const unsigned char *data;
  size_t byteIdx, byteNum;
  unsigned int bytesPerLine;

  bytesPerLine = AIR_MAX(1, nio->charsPerLine/2);
  data = AIR_CAST(const unsigned char*, _data);
  byteNum = elNum*nrrdElementSize(nrrd);
  for (byteIdx=0; byteIdx<byteNum; byteIdx++) {
    fprintf(file, "%c%c",
            _nrrdWriteHexTable[(*data)>>4],
            _nrrdWriteHexTable[(*data)&15]);
    if (bytesPerLine-1 == byteIdx % bytesPerLine) {
      fprintf(file, "\n");
    }
    data++;
  }

  fprintf(file, "\n");
  return 0;
}

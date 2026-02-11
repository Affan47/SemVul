_nrrdEncodingHex_read(FILE *file, void *_data, size_t elNum,
                      Nrrd *nrrd, NrrdIoState *nio) {
  static const char me[]="_nrrdEncodingHex_read";
  size_t nibIdx, nibNum;
  unsigned char *data;
  int car=0, nib;

  AIR_UNUSED(nio);
  data = AIR_CAST(unsigned char *, _data);
  nibIdx = 0;
  nibNum = 2*elNum*nrrdElementSize(nrrd);
  if (nibNum/elNum != 2*nrrdElementSize(nrrd)) {
    biffAddf(NRRD, "%s: size_t can't hold 2*(#bytes in array)\n", me);
    return 1;
  }
  while (nibIdx < nibNum) {
    unsigned char nibshift;
    car = fgetc(file);
    if (EOF == car) break;
    nib = _nrrdReadHexTable[car & 127];
    if (-2 == nib) {

      break;
    }
    if (-1 == nib) {

      continue;
    }

    nibshift = AIR_CAST(unsigned char, nib << (4*(1-(nibIdx & 1))));

    *data = AIR_CAST(unsigned char, *data + nibshift);
    data += nibIdx & 1;
    nibIdx++;
  }
  if (nibIdx != nibNum) {
    char stmp1[AIR_STRLEN_SMALL], stmp2[AIR_STRLEN_SMALL];
    if (EOF == car) {
      biffAddf(NRRD, "%s: hit EOF getting byte %s of %s", me,
               airSprintSize_t(stmp1, nibIdx/2),
               airSprintSize_t(stmp2, nibNum/2));
    } else {
      biffAddf(NRRD, "%s: hit invalid character ('%c') getting "
               "byte %s of %s", me, car,
               airSprintSize_t(stmp1, nibIdx/2),
               airSprintSize_t(stmp2, nibNum/2));
    }
    return 1;
  }
  return 0;
}

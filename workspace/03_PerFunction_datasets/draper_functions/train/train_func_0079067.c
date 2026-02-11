nrrdIoStateSet(NrrdIoState *nio, int parm, int value) {
  static const char me[]="nrrdIoStateSet";

  if (!nio) {
    biffAddf(NRRD, "%s: got NULL pointer", me);
    return 1;
  }
  if (!( AIR_IN_OP(nrrdIoStateUnknown, parm, nrrdIoStateLast) )) {
    biffAddf(NRRD, "%s: identifier %d not in valid range [%d,%d]", me,
             parm, nrrdIoStateUnknown+1, nrrdIoStateLast-1);
    return 1;
  }
  switch (parm) {
  case nrrdIoStateDetachedHeader:
    nio->detachedHeader = !!value;
    break;
  case nrrdIoStateBareText:
    nio->bareText = !!value;
    break;
  case nrrdIoStateCharsPerLine:
    if (value < 40) {
      biffAddf(NRRD, "%s: %d charsPerLine is awfully small", me, value);
      return 1;
    }

    nio->charsPerLine = AIR_CAST(unsigned int, value);
    break;
  case nrrdIoStateValsPerLine:
    if (value < 4) {
      biffAddf(NRRD, "%s: %d valsPerLine is awfully small", me, value);
      return 1;
    }

    nio->valsPerLine = AIR_CAST(unsigned int, value);
    break;
  case nrrdIoStateSkipData:
    nio->skipData = !!value;
    break;
  case nrrdIoStateKeepNrrdDataFileOpen:
    nio->keepNrrdDataFileOpen = !!value;
    break;
  case nrrdIoStateZlibLevel:
    if (!( AIR_IN_CL(-1, value, 9) )) {
      biffAddf(NRRD, "%s: zlibLevel %d invalid", me, value);
      return 1;
    }
    nio->zlibLevel = value;
    break;
  case nrrdIoStateZlibStrategy:
    if (!( AIR_IN_OP(nrrdZlibStrategyUnknown, value, nrrdZlibStrategyLast) )) {
      biffAddf(NRRD, "%s: zlibStrategy %d invalid", me, value);
      return 1;
    }
    nio->zlibStrategy = value;
    break;
  case nrrdIoStateBzip2BlockSize:
    if (!( AIR_IN_CL(-1, value, 9) )) {
      biffAddf(NRRD, "%s: bzip2BlockSize %d invalid", me, value);
      return 1;
    }
    nio->bzip2BlockSize = value;
    break;
  default:
    fprintf(stderr, "!%s: PANIC: didn't recognize parm %d\n", me, parm);
    return 1;
  }
  return 0;
}

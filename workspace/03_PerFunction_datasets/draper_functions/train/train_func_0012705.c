tenFiberParmSet(tenFiberContext *tfx, int parm, double val) {
  static const char me[]="tenFiberParmSet";

  if (tfx) {
    switch(parm) {
    case tenFiberParmStepSize:
      tfx->stepSize = val;
      break;
    case tenFiberParmUseIndexSpace:
      tfx->useIndexSpace = !!val;
      break;
    case tenFiberParmWPunct:
      tfx->wPunct = val;
      break;
    case tenFiberParmVerbose:
      tfx->verbose = AIR_CAST(int, val);
      break;
    default:
      fprintf(stderr, "%s: WARNING!!! tenFiberParm %d not handled\n",
              me, parm);
      break;
    }
  }
  return 0;
}

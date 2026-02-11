deringSliceSet(NrrdDeringContext *drc, deringBag *dbg,
               Nrrd *nout, unsigned int zi) {
  static const char me[]="deringSliceSet";

  if (nrrdWrap_va(dbg->nsliceOut,
                  AIR_CAST(void *, drc->cdataOut + zi*(drc->sliceSize)),
                  nout->type, 2,
                  nout->axis[0].size,
                  nout->axis[1].size)
      || (nrrdTypeDouble == nout->type
          ? nrrdCopy(dbg->nsliceOut, dbg->nslice)
          : nrrdConvert(dbg->nsliceOut, dbg->nslice, nout->type))) {
    biffAddf(NRRD, "%s: slice output trouble", me);
    return 1;
  }

  return 0;
}

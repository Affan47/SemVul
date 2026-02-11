tenFiberMultiNew() {
  static const char me[]="tenFiberMultiNew";
  tenFiberMulti *ret;
  fiberunion tfu;

  ret = AIR_CAST(tenFiberMulti *, calloc(1, sizeof(tenFiberMulti)));
  if (ret) {
    ret->fiber = NULL;
    ret->fiberNum = 0;
    tfu.f = &(ret->fiber);
    ret->fiberArr = airArrayNew(tfu.v, &(ret->fiberNum),
                                sizeof(tenFiberSingle), 512 );
    if (ret->fiberArr) {
      airArrayStructCB(ret->fiberArr,
                       AIR_CAST(void (*)(void *), tenFiberSingleInit),
                       AIR_CAST(void (*)(void *), tenFiberSingleDone));
    } else {
      biffAddf(TEN, "%s: couldn't create airArray", me);
      return NULL;
    }
  } else {
    biffAddf(TEN, "%s: couldn't create tenFiberMulti", me);
    return NULL;
  }
  return ret;
}

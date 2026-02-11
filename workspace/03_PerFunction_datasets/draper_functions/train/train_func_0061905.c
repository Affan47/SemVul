pullCCFind(pullContext *pctx) {
  static const char me[]="pullCCFind";
  airArray *mop, *eqvArr;
  unsigned int passIdx, binIdx, pointIdx, neighIdx, eqvNum,
    pointNum, *idmap;
  pullBin *bin;
  pullPoint *point, *her;

  if (!pctx) {
    biffAddf(PULL, "%s: got NULL pointer", me);
    return 1;
  }
  if (_pullIterate(pctx, pullProcessModeNeighLearn)) {
    biffAddf(PULL, "%s: trouble with %s for CC", me,
             airEnumStr(pullProcessMode, pullProcessModeNeighLearn));
    return 1;
  }

  mop = airMopNew();
  pointNum = pullPointNumber(pctx);
  eqvArr = airArrayNew(NULL, NULL, 2*sizeof(unsigned int), pointNum);
  airMopAdd(mop, eqvArr, (airMopper)airArrayNuke, airMopAlways);
  idmap = AIR_CAST(unsigned int *, calloc(pointNum, sizeof(unsigned int)));
  airMopAdd(mop, idmap, airFree, airMopAlways);


  pctx->idtagNext = 0;
  for (binIdx=0; binIdx<pctx->binNum; binIdx++) {
    bin = pctx->bin + binIdx;
    for (pointIdx=0; pointIdx<bin->pointNum; pointIdx++) {
      point = bin->point[pointIdx];
      point->idtag = pctx->idtagNext++;
    }
  }


  eqvNum = 0;
  for (passIdx=0; passIdx<2; passIdx++) {
    if (passIdx) {
      airArrayLenPreSet(eqvArr, eqvNum);
    }
    for (binIdx=0; binIdx<pctx->binNum; binIdx++) {
      bin = pctx->bin + binIdx;
      for (pointIdx=0; pointIdx<bin->pointNum; pointIdx++) {
        point = bin->point[pointIdx];
        for (neighIdx=0; neighIdx<point->neighPointNum; neighIdx++) {
          if (0 == passIdx) {
            ++eqvNum;
          } else {
            her = point->neighPoint[neighIdx];
            airEqvAdd(eqvArr, point->idtag, her->idtag);
          }
        }
      }
    }
  }


  pctx->CCNum = airEqvMap(eqvArr, idmap, pointNum);


  for (binIdx=0; binIdx<pctx->binNum; binIdx++) {
    bin = pctx->bin + binIdx;
    for (pointIdx=0; pointIdx<bin->pointNum; pointIdx++) {
      point = bin->point[pointIdx];
      point->idCC = idmap[point->idtag];
    }
  }

  airMopOkay(mop);
  return 0;
}

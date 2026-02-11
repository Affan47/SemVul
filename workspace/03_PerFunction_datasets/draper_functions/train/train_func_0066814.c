_pullIterFinishDescent(pullContext *pctx) {
  static const char me[]="_pullIterFinishDescent";
  unsigned int oldBinIdx, pointIdx, taskIdx, runIdx, pointNum;
  pullBin *oldBin;
  pullPoint *point;
  int added;

  _pullNixTheNixed(pctx);

  pctx->stuckNum = 0;
  for (taskIdx=0; taskIdx<pctx->threadNum; taskIdx++) {
    pctx->stuckNum += pctx->task[taskIdx]->stuckNum;
    pctx->task[taskIdx]->stuckNum = 0;
  }


  pointNum = pullPointNumber(pctx);
  if (pointNum != pctx->tmpPointNum) {
    if (pctx->verbose) {
      printf("!%s: changing total point # %u --> %u\n", me,
             pctx->tmpPointNum, pointNum);
    }
    airFree(pctx->tmpPointPerm);
    airFree(pctx->tmpPointPtr);
    pctx->tmpPointPtr = AIR_CAST(pullPoint **,
                                 calloc(pointNum, sizeof(pullPoint*)));
    pctx->tmpPointPerm = AIR_CAST(unsigned int *,
                                  calloc(pointNum, sizeof(unsigned int)));
    if (!( pctx->tmpPointPtr && pctx->tmpPointPerm )) {
      biffAddf(PULL, "%s: couldn't allocate tmp buffers %p %p", me,
               AIR_VOIDP(pctx->tmpPointPtr), AIR_VOIDP(pctx->tmpPointPerm));
      return 1;
    }
    pctx->tmpPointNum = pointNum;
  }
  runIdx = 0;
  for (oldBinIdx=0; oldBinIdx<pctx->binNum; oldBinIdx++) {
    oldBin = pctx->bin + oldBinIdx;
    while (oldBin->pointNum) {


      pctx->tmpPointPtr[runIdx++] = oldBin->point[0];
      _pullBinPointRemove(pctx, oldBin, 0);
    }
  }
  airShuffle_r(pctx->task[0]->rng,
               pctx->tmpPointPerm, pointNum, pctx->flag.permuteOnRebin);
  if (pctx->flag.permuteOnRebin && pctx->verbose) {
    printf("%s: permuting %u points\n", me, pointNum);
  }
  for (pointIdx=0; pointIdx<pointNum; pointIdx++) {
    point = pctx->tmpPointPtr[pctx->tmpPointPerm[pointIdx]];


    if (pctx->constraint && 0 == pctx->constraintDim) {
      if (pullBinsPointMaybeAdd(pctx, point, NULL, &added)) {
        biffAddf(PULL, "%s: trouble binning? point %u", me, point->idtag);
        return 1;
      }
      if (!added) {


        point = pullPointNix(point);
      }
    } else {
      if (pullBinsPointAdd(pctx, point, NULL)) {
        biffAddf(PULL, "%s: trouble binning point %u", me, point->idtag);
        return 1;
      }
      point = NULL;
    }
    pctx->tmpPointPtr[pctx->tmpPointPerm[pointIdx]] = NULL;
  }

  return 0;
}

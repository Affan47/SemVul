tenFiberContextCopy(tenFiberContext *oldTfx) {
  static const char me[]="tenFiberContextCopy";
  tenFiberContext *tfx;

  if (oldTfx->useDwi) {
    fprintf(stderr, "!%s: sorry, can't copy DWI contexts; bye.\n", me);
    exit(1);
  }
  tfx = AIR_CALLOC(1, tenFiberContext);
  memcpy(tfx, oldTfx, sizeof(tenFiberContext));
  tfx->ksp = nrrdKernelSpecCopy(oldTfx->ksp);
  tfx->gtx = gageContextCopy(oldTfx->gtx);
  tfx->pvl = tfx->gtx->pvl[0];
  tfx->gageTen = gageAnswerPointer(tfx->gtx, tfx->pvl, tenGageTensor);
  tfx->gageEval = gageAnswerPointer(tfx->gtx, tfx->pvl, tenGageEval0);

  tfx->gageEvec
    = gageAnswerPointer(tfx->gtx, tfx->pvl,
                        (tenFiberTypeEvec0 == tfx->fiberType
                         ? tenGageEvec0
                         : (tenFiberTypeEvec1 == tfx->fiberType
                            ? tenGageEvec1
                            : tenGageEvec2)));
  tfx->gageAnisoStop = gageAnswerPointer(tfx->gtx, tfx->pvl,
                                         tfx->anisoStopType);
  tfx->gageAnisoSpeed = (tfx->anisoSpeedType
                         ? gageAnswerPointer(tfx->gtx, tfx->pvl,
                                             tfx->anisoSpeedType)
                         : NULL);
  return tfx;
}

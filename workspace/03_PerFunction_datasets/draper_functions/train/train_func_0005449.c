pullConstraintScaleRange(pullContext *pctx, double ssrange[2]) {
  static const char me[]="pullConstraintScaleRange";
  pullVolume *cvol;

  if (!(pctx && ssrange)) {
    biffAddf(PULL, "%s: got NULL pointer", me);
    return 1;
  }
  if (!(pctx->constraint)) {
    biffAddf(PULL, "%s: given context doesn't have constraint set", me);
    return 1;
  }
  if (!(pctx->ispec[pctx->constraint])) {
    biffAddf(PULL, "%s: info %s not set for constriant", me,
             airEnumStr(pullInfo, pctx->constraint));
    return 1;
  }
  cvol = pctx->vol[pctx->ispec[pctx->constraint]->volIdx];
  if (!cvol->ninScale) {
    biffAddf(PULL, "%s: volume \"%s\" has constraint but no scale-space",
             me, cvol->name);
    return 1;
  }
  ssrange[0] = cvol->scalePos[0];
  ssrange[1] = cvol->scalePos[cvol->scaleNum-1];
  if (pctx->flag.scaleIsTau) {
    ssrange[0] = gageTauOfSig(ssrange[0]);
    ssrange[1] = gageTauOfSig(ssrange[1]);
  }

  return 0;
}

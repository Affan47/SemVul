seekUpdate(seekContext *sctx) {
  static const char me[]="seekUpdate";
  int E;

  if (!sctx) {
    biffAddf(SEEK, "%s: got NULL pointer", me);
    return 1;
  }
  E = 0;
  if (!E) E |= updateNinEtAl(sctx);
  if (!E) E |= updateAnswerPointers(sctx);
  if (!E) E |= updateSxSySz(sctx);
  if (!E) E |= updateReverse(sctx);
  if (!E) E |= updateTxfNormal(sctx);
  if (!E) E |= updateSlabCacheAlloc(sctx);
  if (!E) E |= updateSclDerived(sctx);
  if (!E) E |= updateSpanSpaceHist(sctx);
  if (!E) E |= updateResult(sctx);
  if (E) {
    biffAddf(SEEK, "%s: trouble updating", me);
    return 1;
  }

  return 0;
}

_pullConstraintDim(const pullContext *pctx) {
  static const char me[]="_pullConstraintDim";
  int ret, t1, t2, nt1, nt2;

  switch (pctx->constraint) {
  case pullInfoHeightLaplacian:
    ret = 2;
    break;
  case pullInfoIsovalue:
    ret = 2;
    break;
  case pullInfoHeight:
    t1 = !!pctx->ispec[pullInfoTangent1];
    t2 = !!pctx->ispec[pullInfoTangent2];
    nt1 = !!pctx->ispec[pullInfoNegativeTangent1];
    nt2 = !!pctx->ispec[pullInfoNegativeTangent2];
    switch (t1 + t2 + nt1 + nt2) {
    case 0:
    case 3:
      ret = 0;
      break;
    case 1:
      ret = 2;
      break;
    case 2:
      ret = 1;
      break;
    default:
      biffAddf(PULL, "%s: can't simultaneously use all tangents "
               "(%s,%s,%s,%s) as this implies co-dimension of -1", me,
               airEnumStr(pullInfo, pullInfoTangent1),
               airEnumStr(pullInfo, pullInfoTangent2),
               airEnumStr(pullInfo, pullInfoNegativeTangent1),
               airEnumStr(pullInfo, pullInfoNegativeTangent2));
      return -1;
    }
    break;
  default:
    biffAddf(PULL, "%s: constraint on %s (%d) unimplemented", me,
             airEnumStr(pullInfo, pctx->constraint), pctx->constraint);
    return -1;
  }
  return ret;
}

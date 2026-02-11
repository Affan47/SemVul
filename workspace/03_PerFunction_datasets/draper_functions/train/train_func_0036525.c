CConcealment_GetFadeFactor (
      CConcealmentInfo *hConcealmentInfo,
      const int fPreviousFactor
  )
{
  FIXP_DBL fac = (FIXP_DBL)0;

  CConcealParams *pConcealCommonData = hConcealmentInfo->pConcealParams;

  if (hConcealmentInfo->pConcealParams->method > ConcealMethodMute) {
    switch (hConcealmentInfo->concealState) {
      default:
      case ConcealState_Mute:

        break;
      case ConcealState_Ok:
        fac = (FIXP_DBL)MAXVAL_DBL;
        break;
      case ConcealState_Single:
      case ConcealState_FadeOut:
        {
          int idx = hConcealmentInfo->cntFadeFrames - ((fPreviousFactor != 0) ? 1 : 0);
          fac = (idx < 0) ? (FIXP_DBL)MAXVAL_DBL : FX_SGL2FX_DBL(pConcealCommonData->fadeOutFactor[idx]);
        }
        break;
      case ConcealState_FadeIn:
        {
          int idx = hConcealmentInfo->cntFadeFrames + ((fPreviousFactor != 0) ? 1 : 0);
          fac = (idx >= hConcealmentInfo->pConcealParams->numFadeInFrames) ? (FIXP_DBL)0 : FX_SGL2FX_DBL(pConcealCommonData->fadeInFactor[idx]);
        }
        break;
    }
  }

  return (fac);
}

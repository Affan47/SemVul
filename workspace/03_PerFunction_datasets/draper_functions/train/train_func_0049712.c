ApplyOriginShift(T_SgInfo *SgInfo)
{
  int     HaveOrSh, iList, i;
  T_RTMx  *lsmx, SMx;
  int     OrSh[3], lo[3];


  HaveOrSh = 0;

  for (i = 0; i < 3; i++) {
        OrSh[i] = SgInfo->OriginShift[i] * (STBF / 12);
    if (OrSh[i]) HaveOrSh = 1;
  }

  if (HaveOrSh == 0)
    return 0;

  lsmx = SgInfo->ListSeitzMx;

  for (iList = 0; iList < SgInfo->nList; iList++, lsmx++)
  {
    RotMx_t_Vector(lo, lsmx->s.R, OrSh, STBF);

    for (i = 0; i < 3; i++)
      lsmx->s.T[i] = iModPositive(lsmx->s.T[i] - lo[i] + OrSh[i], STBF);
  }

  if (SgInfo->Centric == -1)
  {
    lsmx = &SMx;

    InitSeitzMx(lsmx, -1);

    RotMx_t_Vector(lo, lsmx->s.R, OrSh, STBF);

    for (i = 0; i < 3; i++)
      lsmx->s.T[i] = iModPositive(lsmx->s.T[i] - lo[i] + OrSh[i], STBF);

    if (CoreAdd2ListSeitzMx(SgInfo, lsmx) < 0)
      return -1;

    SgInfo->Centric = 0;
    SgInfo->InversionOffOrigin = 1;
  }

  return 1;
}

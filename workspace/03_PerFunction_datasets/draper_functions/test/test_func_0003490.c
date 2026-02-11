Add2ListSeitzMx(T_SgInfo *SgInfo, const T_RTMx *NewSMx)
{
  int     i, special, Enter;
  int     iMult, jMult;
  T_RTMx  TrialSMx, *iMultSMx, *jMultSMx;

  static const char *Err_Ill_lattice_translation =
    "Error: Illegal lattice translation";


  if (SgInfo->nList == 0)
  {


    InitSeitzMx(&TrialSMx, 1);

    if (CoreAdd2ListSeitzMx(SgInfo, &TrialSMx) < 0)
      return -1;;
  }

  for (i = 0; i < 9; i++)
        TrialSMx.s.R[i] = NewSMx->s.R[i];

  for (i = 0; i < 3; i++) {
        TrialSMx.s.T[i] = NewSMx->s.T[i] % STBF;
    if (TrialSMx.s.T[i] < 0)
        TrialSMx.s.T[i] += STBF;
  }

  iMult = SgInfo->nList;
  iMultSMx = &SgInfo->ListSeitzMx[iMult];

  jMult = 1;
  jMultSMx = &SgInfo->ListSeitzMx[1];

  for (;;)
  {
    Enter = 1;

    special = IsSpecialSeitzMx(SgInfo, &TrialSMx, 1);

    if      (special & SpecialSMx_Identity)
    {
      if (! (special & SpecialSMx_Transl0)) {
        SetSgError(Err_Ill_lattice_translation);
        return -1;
      }

      if (SgInfo->GenOption)
        Enter = 0;
    }
    else if (special & SpecialSMx_Inversion)
    {
      if (! (special & SpecialSMx_Transl0))
      {
        if (SgInfo->Centric) {
          SetSgError(Err_Ill_lattice_translation);
          return -1;
        }

        SgInfo->InversionOffOrigin = 1;
      }
      else
      {
        if (SgInfo->InversionOffOrigin)
          SgInfo->Centric = 1;

        SgInfo->InversionOffOrigin = 0;

        if (SgInfo->GenOption)
        {
          if (SgInfo->Centric == 0)
              SgInfo->Centric = -1;

          Enter = 0;
        }
        else
          SgInfo->Centric = 1;
      }
    }

    if (Enter && CoreAdd2ListSeitzMx(SgInfo, &TrialSMx) < 0)
      return -1;

    if (SgInfo->GenOption < 0)
      break;

    if (jMult > iMult)
    {
      iMult++;
      iMultSMx++;

      jMult = 1;
      jMultSMx = &SgInfo->ListSeitzMx[1];
    }

    if (iMult == SgInfo->nList)
      break;

    SeitzMxMultiply(&TrialSMx, jMultSMx, iMultSMx);

    jMult++;
    jMultSMx++;
  }

  return 0;
}

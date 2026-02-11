CB_SMx(T_RTMx *CSiC,
           const T_RTMx *CBMx, const T_RTMx *SMx, const T_RTMx *InvCBMx)
{
  int     i;
  T_RTMx  BufMx;


  RTMxMultiply(&BufMx, SMx,  InvCBMx, CTBF / STBF, CTBF);
  RTMxMultiply(CSiC,   CBMx, &BufMx,  CRBF,        CRBF * CTBF);

  for (i = 0; i < 9; i++)
  {
    if (CSiC->s.R[i] % (CRBF * CRBF)) {
      SetSgError("Internal Error: Corrupt CBMx/SMx/InvCBMx");
      return -1;
    }

    CSiC->s.R[i] /= (CRBF * CRBF);
  }

  for (i = 0; i < 3; i++)
  {
    if (CSiC->s.T[i] % (CRBF * (CTBF / STBF))) {
      SetSgError("Internal Error: Out of STBF range");
      return -1;
    }

    CSiC->s.T[i] /= (CRBF * (CTBF / STBF));
  }

  return 0;
}

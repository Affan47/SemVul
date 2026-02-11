PostSortSgInfoList(const T_SgInfo *SgInfo, int *List_iList)
{
  int                nList, iL_iL, jL_iL;
  T_RTMx             BufMx1, BufMx2, *smxab;
  const T_RTMx       *lsmx, *smxb;
  T_RotMxInfo        RotMxInfo;
  const T_RotMxInfo  *rmxi;
  int                nO_1, iO, save, i, i_;


  nList = SgInfo->nList;

  iL_iL = 0;

  while (iL_iL < nList)
  {
    lsmx = &SgInfo->ListSeitzMx[List_iList[iL_iL]];

        rmxi = ListOrBufRotMxInfo(SgInfo, List_iList[iL_iL], &RotMxInfo);
    if (rmxi == NULL)
      return -1;

    iL_iL++;

    iO = rmxi->Order;
    if (iO < 0 && iO % 2) iO *= 2;
    nO_1 = abs(iO) - 1;

    smxab = &BufMx2;
    smxb = lsmx;

    for (iO = 1; iO < nO_1; iO++)
    {
      SeitzMxMultiply(smxab, lsmx, smxb);

      for (jL_iL = iL_iL; jL_iL < nList; jL_iL++)
      {
        smxb = &SgInfo->ListSeitzMx[List_iList[jL_iL]];
        if (CompareSeitzMx(SgInfo->LatticeInfo, smxab, smxb) == 0)
          break;
      }

      if (jL_iL < nList)
      {
                              save = List_iList[jL_iL];

        for (i = i_ = jL_iL; i > iL_iL; i = i_)
          List_iList[i] = List_iList[--i_];

        List_iList[iL_iL++] = save;
      }

      smxb = smxab;
      if (iO % 2) smxab = &BufMx1;
      else        smxab = &BufMx2;
    }
  }

  return 0;
}

ListOrBufRotMxInfo(const T_SgInfo *SgInfo, int iList,
                                      T_RotMxInfo *BufRotMxInfo)
{
  T_RotMxInfo  *RMxI;


      RMxI = SgInfo->ListRotMxInfo;
  if (RMxI)
      RMxI += iList;
  else
  {
    RMxI = BufRotMxInfo;

    if (GetRotMxInfo(SgInfo->ListSeitzMx[iList].s.R, RMxI) == 0) {
      SetSgError(Err_Ill_SMx_in_List);
      return NULL;
    }
  }

  return RMxI;
}

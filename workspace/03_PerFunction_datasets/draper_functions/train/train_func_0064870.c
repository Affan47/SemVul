T1_AASetGrayValues(unsigned long white,
		       unsigned long gray75,
		       unsigned long gray50,
		       unsigned long gray25,
		       unsigned long black)
{

  if (T1_CheckForInit()){
    T1_errno=T1ERR_OP_NOT_PERMITTED;
    return(-1);
  }

  gv[4]=(unsigned T1_AA_TYPE32)black;
  gv[3]=(unsigned T1_AA_TYPE32)gray25;
  gv[2]=(unsigned T1_AA_TYPE32)gray50;
  gv[1]=(unsigned T1_AA_TYPE32)gray75;
  gv[0]=(unsigned T1_AA_TYPE32)white;

  T1aa_bg=white;

  if ((T1_AAInit( T1_AA_LOW)))
    return(-1);
  return(0);

}

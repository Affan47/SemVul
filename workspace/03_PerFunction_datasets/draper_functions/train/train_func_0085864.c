hmm_count_logical_num(HTK_HMM_INFO *hmminfo)
{
  HMM_Logical *lg;
  int n;

  n = 0;
  for (lg = hmminfo->lgstart; lg; lg = lg->next) n++;
  hmminfo->totallogicalnum = n;
}

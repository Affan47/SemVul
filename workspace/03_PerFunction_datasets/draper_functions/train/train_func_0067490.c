outprob_cd_max(HMMWork *wrk, int t, CD_State_Set *lset, HTK_Param *param)
{
  LOGPROB maxprob, prob;
  int i;

  maxprob = LOG_ZERO;
  for(i=0;i<lset->num;i++) {
    prob = outprob_state(wrk, t, lset->s[i], param);
    if (maxprob < prob) maxprob = prob;
  }
  return(maxprob);
}

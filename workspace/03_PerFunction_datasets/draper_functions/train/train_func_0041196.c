gprune_heu_init(HMMWork *wrk)
{
  int i;


  wrk->OP_calced_maxnum = wrk->OP_hmminfo->maxmixturenum * wrk->OP_nstream;
  wrk->OP_calced_score = (LOGPROB *)mymalloc(sizeof(LOGPROB) * wrk->OP_calced_maxnum);
  wrk->OP_calced_id = (int *)mymalloc(sizeof(int) * wrk->OP_calced_maxnum);
  wrk->mixcalced = (boolean *)mymalloc(sizeof(int) * wrk->OP_calced_maxnum);
  for(i=0;i<wrk->OP_calced_maxnum;i++) wrk->mixcalced[i] = FALSE;
  wrk->backmax_num = wrk->OP_hmminfo->opt.vec_size + 1;
  wrk->backmax = (LOGPROB *)mymalloc(sizeof(LOGPROB) * wrk->backmax_num);

  return TRUE;
}

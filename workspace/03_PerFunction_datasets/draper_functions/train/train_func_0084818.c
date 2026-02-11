bi_prob_additional_oldbin(NGRAM_INFO *ndata, WORD_ID w1, WORD_ID w2)
{
  NNID n2;
  LOGPROB prob;


  if ((n2 = search_bigram(ndata, w1, w2)) != NNID_INVALID) {
    prob = ndata->p_2[n2];
  } else {
    prob = ndata->bo_wt_1[w1] + ndata->d[0].prob[w2];
  }
  if (w2 != ndata->unk_id) {
    return(prob);
  } else {
    return(prob - ndata->unk_num_log);
  }
}

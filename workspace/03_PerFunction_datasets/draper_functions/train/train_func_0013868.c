hmmlogo_posScoreHeightsDivRelent (P7_HMM *hmm, P7_BG *bg, float *rel_ents, float **heights ) {

  int    K     = hmm->abc->K;
  int    M     = hmm->M;
  int    i, j;

  float p;
  float logodds;
  float pos_scoresum;

  for (i = 1; i <= M; i++) {


    rel_ents[i] = 0;
    pos_scoresum = 0.0;
    for (j=0; j<K; j++) {
      p       = hmm->mat[i][j];
      logodds = eslCONST_LOG2R * log(p / bg->f[j]);
      rel_ents[i] += p==0? 0 : p * logodds ;
      if (logodds > 0)
        pos_scoresum += logodds;
    }


    for (j=0; j<K; j++) {
      p       = hmm->mat[i][j];
      logodds = log(p / bg->f[j]);
      heights[i][j] = logodds<=0 ? 0.0 : (rel_ents[i] * eslCONST_LOG2R * logodds / pos_scoresum) ;
    }

  }
  return eslOK;
}

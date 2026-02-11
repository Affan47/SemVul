Plan7Renormalize(struct plan7_s *hmm)
{
  int   k;
  int   st;
  float d;


  for (k = 1; k <= hmm->M; k++)
    FNorm(hmm->mat[k], Alphabet_size);

  for (k = 1; k < hmm->M; k++)
    FNorm(hmm->ins[k], Alphabet_size);

  d = FSum(hmm->begin+1, hmm->M) + hmm->tbd1;
  FScale(hmm->begin+1, hmm->M, 1./d);
  hmm->tbd1 /= d;

  for (k = 1; k < hmm->M; k++)
    {
      d = FSum(hmm->t[k], 3) + hmm->end[k];
      FScale(hmm->t[k], 3, 1./d);
      hmm->end[k] /= d;

      FNorm(hmm->t[k]+3, 2);
      FNorm(hmm->t[k]+5, 2);
    }

  FNorm(hmm->null, Alphabet_size);

  for (st = 0; st < 4; st++)
    FNorm(hmm->xt[st], 2);


  hmm->t[0][TDM] = hmm->t[0][TDD] = 0.0;

  hmm->flags &= ~PLAN7_HASBITS;
  hmm->flags |= PLAN7_HASPROB;
}

summary_mer(ESL_GETOPTS *go, FILE *fp, struct oneplot_s *plot, double *mervec, double *merthrvec, double *merfpvec, double *merfnvec)
{
  int    nboots              = esl_opt_GetInteger(go, "-N");
  int    by_stddev           = esl_opt_GetBoolean(go, "-s");
  double confidence_interval = esl_opt_GetReal   (go, "--interval");
  double nsd                 = esl_opt_GetReal   (go, "--nsd");
  double mermean, mervar;
  double merthrmean, merthrvar;
  double merfpmean, merfpvar;
  double merfnmean, merfnvar;
  int    ntail;

  esl_stats_DMean(mervec,    nboots, &mermean,    &mervar);
  esl_stats_DMean(merthrvec, nboots, &merthrmean, &merthrvar);
  esl_stats_DMean(merfpvec,  nboots, &merfpmean,  &merfpvar);
  esl_stats_DMean(merfnvec,  nboots, &merfnmean,  &merfnvar);

  esl_vec_DSortIncreasing(mervec,    nboots);
  esl_vec_DSortIncreasing(merthrvec, nboots);
  esl_vec_DSortIncreasing(merfpvec,  nboots);
  esl_vec_DSortIncreasing(merfnvec,  nboots);

  ntail = (int) ((double) nboots * (1.0 - confidence_interval) / 2.0);

  if (by_stddev) {
    fprintf(fp, "[MER: %5.1f %5.1f %5.1f]  ", mermean - nsd*sqrt(mervar), mermean, mermean + nsd*sqrt(mervar));
    fprintf(fp, "[FP: %5.1f %5.1f %5.1f]  ",  merfpmean - nsd*sqrt(merfpvar), merfpmean, merfpmean + nsd*sqrt(merfpvar));
    fprintf(fp, "[FN: %5.1f %5.1f %5.1f]  ",  merfnmean - nsd*sqrt(merfnvar), merfnmean, merfnmean + nsd*sqrt(merfnvar));
    fprintf(fp, "[THR: %5.3f %5.3f %5.3f]\n", merthrmean - nsd*sqrt(merthrvar), merthrmean, merthrmean + nsd*sqrt(merthrvar));
  }
  else {
    fprintf(fp, "[MER: %5.1f %5.1f %5.1f]  ", mervec[ntail], mermean, mervec[nboots-ntail]);
    fprintf(fp, "[FN: %5.1f %5.1f %5.1f]  ", merfnvec[ntail], merfnmean, merfnvec[nboots-ntail]);
    fprintf(fp, "[FP: %5.1f %5.1f %5.1f]  ", merfpvec[ntail], merfpmean, merfpvec[nboots-ntail]);
    fprintf(fp, "[THR: %5.3f %5.3f %5.3f]\n", merthrvec[ntail], merthrmean, merthrvec[nboots-ntail]);
  }
}

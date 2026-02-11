cm_pli_Statistics(FILE *ofp, CM_PIPELINE *pli, ESL_STOPWATCH *w)
{
  if(pli->nmodels > 0 && pli->be_verbose) {
    pli_pass_statistics(ofp, pli, PLI_PASS_STD_ANY); fprintf(ofp, "\n");
    if(pli->do_trunc_ends) {
      pli_pass_statistics(ofp, pli, PLI_PASS_5P_ONLY_FORCE);   fprintf(ofp, "\n");
      pli_pass_statistics(ofp, pli, PLI_PASS_3P_ONLY_FORCE);   fprintf(ofp, "\n");
      pli_pass_statistics(ofp, pli, PLI_PASS_5P_AND_3P_FORCE); fprintf(ofp, "\n");
    }
    else if(pli->do_trunc_any) {
      pli_pass_statistics(ofp, pli, PLI_PASS_5P_AND_3P_ANY); fprintf(ofp, "\n");
    }
  }
  if(pli->nmodels_hmmonly > 0) {
    pli_hmmonly_pass_statistics(ofp, pli); fprintf(ofp, "\n");
  }
  if(pli->nmodels > 0) {
    pli_sum_statistics(pli);
    pli_pass_statistics(ofp, pli, PLI_PASS_CM_SUMMED); fprintf(ofp, "\n");
  }
  if(pli->nmodels > 0 && pli->nmodels_hmmonly > 0) {
    fprintf(ofp, "Total CM and HMM hits reported:                    %15d\n\n",
	    (int) (pli->acct[PLI_PASS_CM_SUMMED].n_output) +
	    (int) (pli->acct[PLI_PASS_HMM_ONLY_ANY].n_output));
  }
  if(w != NULL) esl_stopwatch_Display(ofp, w, "# CPU time: ");

  return eslOK;
}

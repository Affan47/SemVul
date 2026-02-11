fm_initConfigGeneric( FM_CFG *cfg, ESL_GETOPTS *go ) {

  cfg->maskSA       =  cfg->meta->freq_SA - 1;
  cfg->shiftSA      =  cfg->meta->SA_shift;

  cfg->msv_length      = (go ? esl_opt_GetInteger(go, "--fm_msv_length") : -1);
  cfg->max_depth       = (go ? esl_opt_GetInteger(go, "--fm_max_depth") :  -1);
  cfg->neg_len_limit   = (go ? esl_opt_GetInteger(go, "--fm_max_neg_len") : -1);
  cfg->consec_pos_req  = (go ? esl_opt_GetInteger(go, "--fm_req_pos") : -1);
  cfg->score_ratio_req = (go ? esl_opt_GetReal(go, "--fm_sc_ratio") : -1.0);
  cfg->max_scthreshFM  = (go ? esl_opt_GetReal(go, "--fm_max_scthresh") : -1.0);


  return eslOK;
}

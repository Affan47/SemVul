p7_pli_NewModel(P7_PIPELINE *pli, const P7_OPROFILE *om, P7_BG *bg)
{
  int status = eslOK;

  pli->nmodels++;
  pli->nnodes += om->M;
  if (pli->Z_setby == p7_ZSETBY_NTARGETS && pli->mode == p7_SCAN_MODELS) pli->Z = pli->nmodels;

  if (pli->do_biasfilter) p7_bg_SetFilter(bg, om->M, om->compo);

  if (pli->mode == p7_SEARCH_SEQS)
    status = p7_pli_NewModelThresholds(pli, om);

  pli->W = om->max_length;

  return status;
}

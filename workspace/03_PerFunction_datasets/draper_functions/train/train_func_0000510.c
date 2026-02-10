gms_free(HMMWork *wrk)
{
  free_gsset(wrk);
  free_state2gs(wrk);
  free(wrk->gsindex);
  if (wrk->fallback_score != NULL) {
    free(wrk->fallback_score[0]);
    free(wrk->fallback_score);
    free(wrk->gms_is_selected);
  }
  gms_gprune_free(wrk);
}

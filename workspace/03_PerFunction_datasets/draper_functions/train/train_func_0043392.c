cm_tophits_UpdateHitPositions(CM_TOPHITS *th, int hit_start, int64_t seq_start, int in_revcomp)
{
  int i;
  if(in_revcomp) {
    for (i = hit_start; i < th->N ; i++) {
      th->unsrt[i].start = seq_start - th->unsrt[i].start + 1;
      th->unsrt[i].stop  = seq_start - th->unsrt[i].stop  + 1;
      th->unsrt[i].in_rc = TRUE;
      if(th->unsrt[i].ad != NULL) {
	th->unsrt[i].ad->sqfrom = seq_start - th->unsrt[i].ad->sqfrom + 1;
	th->unsrt[i].ad->sqto   = seq_start - th->unsrt[i].ad->sqto + 1;
      }
    }

  }
  else {
    for (i = hit_start; i < th->N ; i++) {
      th->unsrt[i].start += seq_start-1;
      th->unsrt[i].stop  += seq_start-1;
      th->unsrt[i].in_rc = FALSE;
      if(th->unsrt[i].ad != NULL) {
	th->unsrt[i].ad->sqfrom += seq_start-1;
	th->unsrt[i].ad->sqto   += seq_start-1;
      }
    }
  }
  return eslOK;
}

prepare_sspbittab_and_shortest(unsigned long totallength,
    ContfindBUstate *state)
{
  unsigned long length, lastseqstart, i, ssp;

  GT_INITBITTAB(state->sspbittab, totallength + 1);
  lastseqstart = 0;
  state->shortest = totallength;
  for (i = 1UL; i <= state->nofsequences - 1; i++)
  {
    ssp = gt_encseq_seqstartpos(state->encseq, i) - 1;
    GT_SETIBIT(state->sspbittab, ssp);
    length = ssp - lastseqstart;
    lastseqstart = ssp + 1;
    if (length < state->shortest)
      state->shortest = length;
  }
  GT_SETIBIT(state->sspbittab, totallength);
  length = totallength - lastseqstart;
  if (length < state->shortest)
    state->shortest = length;
}

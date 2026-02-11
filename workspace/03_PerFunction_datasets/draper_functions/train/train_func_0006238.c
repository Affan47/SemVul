gt_reads2twobit_append_seppos(GtReads2TwobitEncodeState *state)
{
  gt_assert(state->seppos != NULL);
  if (state->current.seppos_nextfree == state->seppos_alloc)
  {
    (state->seppos_alloc) += GT_READS2TWOBIT_SEPPOS_INC;
    state->seppos = gt_realloc(state->seppos,
        sizeof (state->seppos) * state->seppos_alloc);
  }
  gt_assert(state->current.globalpos > 0);
  state->seppos[state->current.seppos_nextfree] =
    state->current.globalpos - 1UL;
  state->current.seppos_nextfree++;
}

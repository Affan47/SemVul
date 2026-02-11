gt_reads2twobit_process_fastq_mate_pair(
    GtReads2TwobitEncodeState *state, char *line2, FILE *file2, bool *file2new)
{
  int had_err = 0;
  char *fgetsretval = NULL;
  bool was_invalid = state->invalid_mode;
  unsigned long prev_seqlen = state->seqlen;
  unsigned long qbuf2_next = 0;
  bool qmode = false;
  if (*file2new)
  {
    fgetsretval = fgets(line2, (int)GT_READS2TWOBIT_READBUFFER_SIZE, file2);
    gt_assert(fgetsretval == line2);
    *file2new = false;
  }
  GT_READS2TWOBIT_SKIP_TO_DESCRIPTION_END(line2, file2, fgetsretval);
  state->seqlen_mate = state->seqlen;
  state->seqlen = 0;
  if (!state->invalid_mode)
    state->current.nofseqs++;
  else
    state->invalid_sequences++;
  while (!had_err)
  {
    fgetsretval = fgets(line2, (int)GT_READS2TWOBIT_READBUFFER_SIZE, file2);
    if (fgetsretval == NULL)
      break;
    if (!qmode)
    {
      if (line2[0] == '@')
        break;
      else if (line2[0] == '+')
      {
        GT_READS2TWOBIT_SKIP_TO_DESCRIPTION_END(line2, file2, fgetsretval);
        if (state->seqlen + 1UL > (unsigned long)(state->qbuf2_size))
        {
          state->qbuf2_size = (size_t)state->seqlen + 1;
          state->qbuf2 = gt_realloc(state->qbuf2, state->qbuf2_size);
        }
        qmode = true;
      }
      else
      {
        gt_reads2twobit_process_sequence_line(state, line2);
      }
    }
    else
    {
      had_err = gt_reads2twobit_process_qualities_line(state, line2,
          state->qbuf2, &qbuf2_next);
      if (had_err == -1)
        had_err = -2;
      if (!had_err && qbuf2_next == state->seqlen)
      {
        if (state->maxlow != GT_UNDEF_ULONG)
          gt_reads2twobit_apply_quality_filter(state, state->qbuf2, qbuf2_next);
        qbuf2_next = 0;
        qmode = false;
      }
    }
  }
  if (!had_err && !state->invalid_mode)
    gt_reads2twobit_process_sequence_end(state);
  if (!had_err && !was_invalid && state->invalid_mode)
  {
    state->invalid_sequences++;
    state->invalid_total_length += (prev_seqlen - 1UL);
  }
  return had_err;
}

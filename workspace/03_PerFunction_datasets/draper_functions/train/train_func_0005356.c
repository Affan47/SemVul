gt_reads2twobit_encode_unpaired_library(
    GtReads2TwobitEncodeState *state, GtReadsLibraryInfo *rli, GtError *err)
{
  int had_err = 0;
  FILE *file;
  file = gt_fa_fopen(gt_str_get(rli->filename1), "r", err);
  if (file == NULL)
    had_err = -1;
  if (!had_err)
  {
    const unsigned long invalid_tl_before = state->invalid_total_length,
          invalid_s_before = state->invalid_sequences;
    char line[GT_READS2TWOBIT_READBUFFER_SIZE], *fgetsretval;
    rli->first_seqnum = state->current.nofseqs;
    fgetsretval = fgets(line, (int)GT_READS2TWOBIT_READBUFFER_SIZE, file);
    if (fgetsretval == line)
    {
      if (line[0] == '>')
      {
        gt_reads2twobit_encode_unpaired_fasta_library(state, rli, file, line);
      }
      else if (line[0] == '@')
      {
        had_err = gt_reads2twobit_encode_unpaired_fastq_library(state, rli,
            file, line);
        if (had_err != 0)
          gt_error_set(err, "%s: error in FASTQ format",
              gt_str_get(rli->filename1));
      }
      else
      {
        gt_error_set(err, "%s: unknown format", gt_str_get(rli->filename1));
        had_err = -1;
      }
    }
    else
    {

      gt_assert(fgetsretval == NULL);
    }
    if (!state->invalid_mode)
      gt_reads2twobit_process_sequence_end(state);
    gt_assert(state->current.nofseqs >= rli->first_seqnum);
    rli->nofseqs = state->current.nofseqs - rli->first_seqnum;
    rli->total_seqlength = state->varlen_mode
      ?  state->seppos[state->current.nofseqs - 1UL] + 1UL -
         ((rli->first_seqnum == 0) ? 0 : state->seppos[rli->first_seqnum - 1UL])
      : state->seqlen_first * rli->nofseqs;

    rli->total_filelength -= (state->invalid_total_length - invalid_tl_before +
        3UL * (state->invalid_sequences - invalid_s_before));
    if (!had_err)
      had_err = gt_reads2twobit_close_file(file, rli->filename1, err);
    else
      gt_fa_fclose(file);
  }
  return had_err;
}

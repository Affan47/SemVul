gt_hcr_decoder_decode_range(GtHcrDecoder *hcr_dec, const char *name,
                                unsigned long start, unsigned long end,
                                GtTimer *timer, GtError *err)
{
  char qual[BUFSIZ] = {0},
       seq[BUFSIZ] = {0};
  GtStr *desc = gt_str_new();
  int had_err = 0;
  unsigned long cur_width,
                cur_read;
  size_t i;
  FILE *output;
  GT_UNUSED GtHcrSeqDecoder *seq_dec;

  gt_error_check(err);
  gt_assert(hcr_dec && name);
  seq_dec = hcr_dec->seq_dec;
  gt_assert(start <= end);
  gt_assert(start < seq_dec->num_of_reads && end < seq_dec->num_of_reads);
  if (timer != NULL)
    gt_timer_show_progress(timer, "decode hcr", stdout);
  output = gt_fa_fopen_with_suffix(name, HCRFILEDECODEDSUFFIX, "w", err);
  if (output == NULL)
    had_err = -1;

  for (cur_read = start; had_err == 0 && cur_read <= end; cur_read++) {
    if (gt_hcr_decoder_decode(hcr_dec, cur_read, seq, qual, desc, err) != 0)
      had_err = -1;
    else {
      gt_xfputc(HCR_DESCSEPSEQ, output);
      if (hcr_dec->encdesc != NULL)
        gt_xfputs(gt_str_get(desc), output);
      else
        fprintf(output, "%lu", cur_read);
      gt_xfputc('\n', output);
      for (i = 0, cur_width = 0; i < strlen(seq); i++, cur_width++) {
        if (cur_width == HCR_LINEWIDTH) {
          cur_width = 0;
          gt_xfputc('\n', output);
        }
        gt_xfputc(seq[i], output);
      }
      gt_xfputc('\n', output);
      gt_xfputc(HCR_DESCSEPQUAL, output);
      gt_xfputc('\n', output);
      for (i = 0, cur_width = 0; i < strlen(qual); i++, cur_width++) {
        if (cur_width == HCR_LINEWIDTH) {
          cur_width = 0;
          gt_xfputc('\n', output);
        }
        gt_xfputc(qual[i], output);
      }
      gt_xfputc('\n', output);
    }
  }
  gt_fa_xfclose(output);
  gt_str_delete(desc);
  return had_err;
}

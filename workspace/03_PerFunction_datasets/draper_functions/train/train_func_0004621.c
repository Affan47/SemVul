gth_input_original_genomic_sequence(GthInput *input,
                                                         GT_UNUSED
                                                         unsigned long filenum,
                                                         bool forward)
{
  gt_assert(input);
  gt_assert(input->gen_file_num == filenum);
  if (forward)
    return gth_seq_con_get_orig_seq(input->gen_seq_con, 0);
  else {
    gt_assert(input->searchmode & GTHREVERSE);
    return gth_seq_con_get_orig_seq_rc(input->gen_seq_con, 0);
  }
}

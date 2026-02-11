gth_input_num_of_gen_seqs(GthInput *input,
                                        GT_UNUSED unsigned long filenum)
{
  gt_assert(input);
  gt_assert(input->gen_file_num == filenum);
  return gth_seq_con_num_of_seqs(input->gen_seq_con);
}

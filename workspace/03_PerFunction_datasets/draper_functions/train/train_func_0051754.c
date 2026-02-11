gth_input_get_genomic_description(GthInput *input, GtStr *description,
                                       GT_UNUSED unsigned long filenum,
                                       unsigned long seqnum)
{
  gt_assert(input && description);
  gt_assert(input->gen_file_num == filenum);
  gth_seq_con_get_description(input->gen_seq_con, seqnum, description);
}

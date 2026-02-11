gth_sa_echo_genomic_description(const GthSA *sa, GthInput *input,
                                     GtFile *outfp)
{
  gt_assert(sa && input);
  gth_input_echo_genomic_description(input, sa->gen_file_num,
                                     sa->gen_seq_num, outfp);
}

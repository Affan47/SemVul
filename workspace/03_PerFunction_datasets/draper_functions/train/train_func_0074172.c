chaining_info_init(GthChainingInfo *chaining_info,
                               bool directmatches,
                               bool refseqisdna,
                               GthCallInfo *call_info,
                               GthInput *input,
                               GthStat *stat,
                               unsigned long gen_file_num,
                               unsigned long ref_file_num)
{
  chaining_info->directmatches    = directmatches;
  chaining_info->refseqisindex    = call_info->simfilterparam.inverse ||
                                    !refseqisdna;
  chaining_info->jtdebug          = call_info->dp_options_core->jtdebug;
  chaining_info->call_info        = call_info;
  chaining_info->input            = input;
  chaining_info->stat             = stat;
  chaining_info->gen_file_num     = gen_file_num;
  chaining_info->ref_file_num     = ref_file_num;
  chaining_info->bucketnum        = 0;
  chaining_info->maxbucketnum     = ~0;
}

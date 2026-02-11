gt_gff3_in_stream_enable_tidy_mode(GtGFF3InStream *is)
{
  gt_assert(is);
  gt_gff3_in_stream_plain_enable_tidy_mode(is->gff3_in_stream_plain);
  gt_cds_check_stream_enable_tidy_mode((GtCDSCheckStream*)
                                       is->cds_check_stream);
}

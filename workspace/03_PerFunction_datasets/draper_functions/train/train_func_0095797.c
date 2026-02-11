gt_gtf_to_gff3_runner(GT_UNUSED int argc, const char **argv,
                                 int parsed_args, void *tool_arguments,
                                 GtError *err)
{
  GTFToGFF3Arguments *arguments = tool_arguments;
  GtNodeStream *gtf_in_stream = NULL, *gff3_out_stream = NULL;
  int had_err;

  gt_error_check(err);
  gt_assert(arguments);


  gtf_in_stream = gt_gtf_in_stream_new(argv[parsed_args]);
  if (arguments->tidy)
    gt_gtf_in_stream_enable_tidy_mode(gtf_in_stream);


  gff3_out_stream = gt_gff3_out_stream_new(gtf_in_stream, arguments->outfp);


  had_err = gt_node_stream_pull(gff3_out_stream, err);


  gt_node_stream_delete(gff3_out_stream);
  gt_node_stream_delete(gtf_in_stream);

  return had_err;
}

gt_mergefeat_runner(int argc, const char **argv, int parsed_args,
                          void *tool_arguments, GtError *err)
{
  InterFeatArguments *arguments = tool_arguments;
  GtNodeStream *gff3_in_stream,
               *merge_feature_stream,
               *gff3_out_stream;
  int had_err;

  gt_error_check(err);
  gt_assert(arguments);


  gff3_in_stream = gt_gff3_in_stream_new_unsorted(argc - parsed_args,
                                                  argv + parsed_args);


  merge_feature_stream = gt_merge_feature_stream_new(gff3_in_stream);


  gff3_out_stream = gt_gff3_out_stream_new(merge_feature_stream,
                                           arguments->outfp);


  had_err = gt_node_stream_pull(gff3_out_stream, err);


  gt_node_stream_delete(gff3_out_stream);
  gt_node_stream_delete(merge_feature_stream);
  gt_node_stream_delete(gff3_in_stream);

  return had_err;
}

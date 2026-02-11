bed_in_stream_process_file(GtBEDInStream *bed_in_stream,
                                      GtError *err)
{
  int had_err;
  gt_error_check(err);
  gt_assert(bed_in_stream);
  had_err = gt_bed_parser_parse(bed_in_stream->bed_parser,
                                bed_in_stream->genome_node_buffer,
                                bed_in_stream->filename, err);
  return had_err;
}

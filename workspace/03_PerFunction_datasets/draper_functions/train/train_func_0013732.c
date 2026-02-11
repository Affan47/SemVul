gt_shredder_option_parser_new(void *tool_arguments)
{
  ShredderArguments *arguments = tool_arguments;
  GtOptionParser *op;
  GtOption *o;
  gt_assert(arguments);
  op = gt_option_parser_new("[option ...] [sequence_file ...]",
                            "Shredder sequence file(s) into consecutive pieces "
                            "of random length.");
  o = gt_option_new_ulong_min("coverage", "set the number of times the "
                              "sequence_file is shreddered",
                              &arguments->coverage, 1, 1);
  gt_option_parser_add_option(op, o);
  o = gt_option_new_ulong("minlength",
                          "set the minimum length of the shreddered "
                          "fragments", &arguments->minlength, 300);
  gt_option_parser_add_option(op, o);
  o = gt_option_new_ulong("maxlength",
                          "set the maximum length of the shreddered "
                          "fragments", &arguments->maxlength, 700);
  gt_option_parser_add_option(op, o);
  o = gt_option_new_ulong("overlap", "set the overlap between consecutive "
                          "pieces", &arguments->overlap, 0);
  gt_option_parser_add_option(op, o);
  o = gt_option_new_probability("sample", "take samples of the generated "
                                "sequences pieces with the given probability",
                                &arguments->sample_probability, 1.0);
  gt_option_parser_add_option(op, o);
  o = gt_option_new_width(&arguments->width);
  gt_option_parser_add_option(op, o);
  gt_output_file_register_options(op, &arguments->outfp, arguments->ofi);
  gt_option_parser_set_comment_func(op, gt_gtdata_show_help, NULL);
  return op;
}

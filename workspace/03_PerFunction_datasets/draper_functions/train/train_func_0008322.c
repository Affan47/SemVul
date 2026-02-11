gt_extractseq_option_parser_new(void *tool_arguments)
{
  ExtractSeqArguments *arguments = tool_arguments;
  GtOptionParser *op;
  GtOption *frompos_option, *topos_option, *match_option, *width_option,
         *fastakeyfile_option;
  gt_assert(arguments);


  op = gt_option_parser_new("[option ...] [sequence_file(s)] | fastaindex",
                            "Extract sequences from given sequence file(s) or "
                            "fastaindex.");


  frompos_option = gt_option_new_ulong_min(FROMPOS_OPTION_STR,
                                        "extract sequence from this position\n"
                                        "counting from 1 on",
                                        &arguments->frompos, 0, 1UL);
  gt_option_parser_add_option(op, frompos_option);


  topos_option = gt_option_new_ulong_min(TOPOS_OPTION_STR,
                                      "extract sequence up to this position\n"
                                      "counting from 1 on",
                                      &arguments->topos, 0, 1UL);
  gt_option_parser_add_option(op, topos_option);


  match_option = gt_option_new_string("match", "extract all sequences whose "
                                   "description matches the given pattern.\n"
                                   "The given pattern must be a valid extended "
                                   "regular expression.", arguments->pattern,
                                   NULL);
  gt_option_parser_add_option(op, match_option);


  fastakeyfile_option = gt_option_new_filename("keys",
                                               "extract substrings for keys "
                                               "in specified file",
                                     arguments->fastakeyfile);
  gt_option_parser_add_option(op, fastakeyfile_option);


  width_option = gt_option_new_width(&arguments->width);
  gt_option_parser_add_option(op, width_option);


  gt_output_file_register_options(op, &arguments->outfp, arguments->ofi);


  gt_option_imply(frompos_option, topos_option);
  gt_option_imply(topos_option, frompos_option);


  gt_option_exclude(frompos_option, match_option);
  gt_option_exclude(topos_option, match_option);
  gt_option_exclude(frompos_option, fastakeyfile_option);
  gt_option_exclude(match_option, fastakeyfile_option);

  gt_option_parser_set_comment_func(op, gt_gtdata_show_help, NULL);
  return op;
}

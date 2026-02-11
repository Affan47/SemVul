gt_splicesiteinfo_option_parser_new(void *tool_arguments)
{
  SpliceSiteInfoArguments *arguments = tool_arguments;
  GtOptionParser *op;
  GtOption *option;
  gt_assert(arguments);

  op = gt_option_parser_new("[option ...] [GFF3_file ...]", "Show information "
                            "about splice sites given in GFF3 files.");


  gt_seqid2file_register_options(op, arguments->s2fi);


  option = gt_option_new_bool("addintrons", "add intron features between "
                              "existing exon features\n(before computing the "
                              "information to be shown)",
                              &arguments->addintrons, false);
  gt_option_parser_add_option(op, option);


  gt_output_file_register_options(op, &arguments->outfp, arguments->ofi);

  gt_option_parser_set_comment_func(op, gt_gtdata_show_help, NULL);

  return op;
}

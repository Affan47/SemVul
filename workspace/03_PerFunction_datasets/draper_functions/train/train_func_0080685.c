gt_sain_option_parser_new(void *tool_arguments)
{
  GtSainArguments *arguments = tool_arguments;
  GtOptionParser *op;
  GtOption *option, *optionfcheck, *optionesq, *optionfile;

  gt_assert(arguments != NULL);


  op = gt_option_parser_new("[option ...] [file]",
                            "Compute suffix array using induced "
                            "suffix sorting.");
  gt_option_parser_set_mail_address(op,"<kurtz@zbh.uni-hamburg.de>");


  optionesq = gt_option_new_string("esq", "specify encseq file",
                             arguments->encseqfile, NULL);
  gt_option_parser_add_option(op, optionesq);


  gt_encseq_options_add_readmode_option(op, arguments->dir);


  optionfile = gt_option_new_string("file", "specify filename",
                                   arguments->plainseqfile, NULL);
  gt_option_parser_add_option(op, optionfile);


  option = gt_option_new_bool("icheck",
                              "intermediate check of all sorted arrays",
                              &arguments->icheck, false);
  gt_option_parser_add_option(op, option);


  optionfcheck = gt_option_new_bool("fcheck", "final check of suffix array",
                                    &arguments->fcheck, false);
  gt_option_parser_add_option(op, optionfcheck);
  gt_option_imply(optionfcheck, optionesq);
  gt_option_exclude(optionesq,optionfile);


  option = gt_option_new_verbose(&arguments->verbose);
  gt_option_parser_add_option(op, option);

  return op;
}

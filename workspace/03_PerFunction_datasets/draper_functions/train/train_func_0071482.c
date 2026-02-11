parse_options(Pmatchoptions *pmopt,
                              int *parsed_args,
                              int argc, const char **argv, GtError *err)
{
  GtOptionParser *op;
  GtOption *option, *optionimm, *optionbck;
  GtOPrval oprval;

  gt_error_check(err);
  op = gt_option_parser_new("[options] -ii indexname",
                         "Perform pattern matches.");
  gt_option_parser_set_mail_address(op, "<kurtz@zbh.uni-hamburg.de>");

  option = gt_option_new_ulong("minpl","Specify minimum length of pattern",
                           &pmopt->minpatternlen,
                           (unsigned long) 20);
  gt_option_parser_add_option(op, option);
  option = gt_option_new_ulong("maxpl","Specify maximum length of pattern",
                            &pmopt->maxpatternlen,
                            (unsigned long) 30);
  gt_option_parser_add_option(op, option);

  option = gt_option_new_ulong("samples","Specify number of samples",
                            &pmopt->numofsamples,
                           (unsigned long) 100000);
  gt_option_parser_add_option(op, option);

  option = gt_option_new_bool("s","Show generated pattern",
                            &pmopt->showpatt,
                            false);
  gt_option_parser_add_option(op, option);

  optionbck = gt_option_new_bool("bck","Use the bucket boundaries",
                              &pmopt->usebcktab,
                              false);
  gt_option_parser_add_option(op, optionbck);

  optionimm = gt_option_new_bool("imm","Start with offset 0",
                              &pmopt->immediate,
                              false);
  gt_option_parser_add_option(op, optionimm);

  option = gt_option_new_string("ii",
                             "Specify input index",
                             pmopt->indexname, NULL);
  gt_option_parser_add_option(op, option);
  gt_option_is_mandatory(option);

  oprval = gt_option_parser_parse(op, parsed_args, argc, argv,
                               gt_versionfunc, err);
  gt_option_parser_delete(op);

  return oprval;
}

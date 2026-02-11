parse_options(int *parsed_args, RegionCovArguments *arguments,
                              int argc, const char **argv, GtError *err)
{
  GtOptionParser *op;
  GtOption *o;
  GtOPrval oprval;
  gt_error_check(err);
  op = gt_option_parser_new("[option ...] GFF3_file",
                         "Show which parts of the given sequence regions are "
                         "covered by features.");

  o = gt_option_new_ulong("maxfeaturedist", "set the maximum distance two "
                       "features can have while still being in the same "
                       "``cluster''", &arguments->max_feature_dist, 0);
  gt_option_parser_add_option(op, o);

  o = gt_option_new_verbose(&arguments->verbose);
  gt_option_parser_add_option(op, o);

  gt_option_parser_set_min_max_args(op, 1, 1);
  oprval = gt_option_parser_parse(op, parsed_args, argc, argv, gt_versionfunc,
                                  err);
  gt_option_parser_delete(op);
  return oprval;
}

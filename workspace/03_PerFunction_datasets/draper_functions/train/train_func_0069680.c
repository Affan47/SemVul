gthsplit_parse_options(int *parsed_args,
                                       Gthsplitinfo *gthsplitinfo,
                                       int argc, const char **argv,
                                       const GthPlugins *plugins, GtError *err)
{
  GtOptionParser *op;
  GtOption *optalignmentscore, *optcoverage, *optrange, *optverbose, *optgzip,
           *optbzip2, *optforce;
  bool alignmentscore, coverage, verbose, gzip, bzip2;
  GtOPrval oprval;

  gt_error_check(err);

  op = gt_option_parser_new("-alignmentscore | -coverage [option ...] "
                            "[file ...]", "Split GenomeThreader output files "
                            "containing intermediate results.");


  optalignmentscore = gt_option_new_bool("alignmentscore", "split according to "
                                      "the overall alignment score (scr)",
                                      &alignmentscore, false);
  gt_option_parser_add_option(op, optalignmentscore);

  optcoverage = gt_option_new_bool("coverage", "split according to coverage "
                                   "(cov)", &coverage, false);
  gt_option_parser_add_option(op, optcoverage);

  optrange = gt_option_new_uint_max(RANGE_OPT_CSTR, "set the percentage range "
                                 "used to create the sets",
                                 &gthsplitinfo->range, DEFAULT_RANGE, 100);
  gt_option_parser_add_option(op, optrange);


  gth_sa_filter_register_options(op, gthsplitinfo->sa_filter, false);


  optverbose = gt_option_new_verbose(&verbose);
  gt_option_parser_add_option(op, optverbose);

  optgzip = gt_option_new_bool("gzip", "write gzip compressed output file(s)",
                               &gzip, false);
  gt_option_parser_add_option(op, optgzip);

  optbzip2 = gt_option_new_bool("bzip2", "write bzip2 compressed output "
                                "file(s)", &bzip2, false);
  gt_option_parser_add_option(op, optbzip2);

  optforce = gt_option_new_bool(GT_FORCE_OPT_CSTR,"force writing to split "
                                "files", &gthsplitinfo->force, false);
  gt_option_parser_add_option(op, optforce);

  gt_option_exclude(optalignmentscore, optcoverage);
  gt_option_exclude(optgzip, optbzip2);
  gt_option_is_mandatory_either(optalignmentscore, optcoverage);

  gt_option_parser_set_mail_address(op, "<gremme@zbh.uni-hamburg.de>");
  oprval = gt_option_parser_parse(op, parsed_args, argc, argv,
                                  plugins->gth_version_func, err);

  if (oprval == GT_OPTION_PARSER_OK && alignmentscore)
    gthsplitinfo->splitmode = ALIGNMENTSCORE_SPLIT;
  if (oprval == GT_OPTION_PARSER_OK && coverage)
    gthsplitinfo->splitmode = COVERAGE_SPLIT;
  if (oprval == GT_OPTION_PARSER_OK && 100 % gthsplitinfo->range) {
    gt_error_set(err, "argument to option %s must divide 100 without rest",
              RANGE_OPT_CSTR);
    oprval = GT_OPTION_PARSER_ERROR;
  }
  if (oprval == GT_OPTION_PARSER_OK && verbose)
    gthsplitinfo->showverbose = gth_show_on_stdout;
  if (oprval == GT_OPTION_PARSER_OK && gzip)
    gthsplitinfo->file_mode = GT_FILE_MODE_GZIP;
  if (oprval == GT_OPTION_PARSER_OK && bzip2)
    gthsplitinfo->file_mode = GT_FILE_MODE_BZIP2;


  if (oprval == GT_OPTION_PARSER_OK) {
    while (*parsed_args < argc) {
      gt_str_array_add_cstr(gthsplitinfo->consensusfiles, argv[*parsed_args]);
      (*parsed_args)++;
    }
  }

  if (oprval == GT_OPTION_PARSER_OK &&
      !gt_str_array_size(gthsplitinfo->consensusfiles) &&
      (gt_option_is_set(optgzip) || gt_option_is_set(optbzip2))) {
    gt_error_set(err, "to use compression, at least on input file has to be "
                      "supplied");
    oprval = GT_OPTION_PARSER_ERROR;
  }

  gt_option_parser_delete(op);

  return oprval;
}

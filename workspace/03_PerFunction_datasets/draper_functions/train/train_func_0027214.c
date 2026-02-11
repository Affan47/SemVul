gt_simreads_option_parser_new(void *tool_arguments)
{
  GtSimreadsArguments *arguments = tool_arguments;
  GtOptionParser *op;
  GtOption *num_option, *coverage_option, *len_option,
           *minlen_option, *maxlen_option, *p_option, *v_option,
           *dl_option, *ds_option, *ss_option, *distlen_option;

  gt_assert(arguments);


  op = gt_option_parser_new("[option ...] <encseq>",
                         "Simulate sequencing reads from "
                         "random positions in the input sequence(s).");


  num_option = gt_option_new_ulong_min("num", "desired number of reads",
                                       &arguments->num, GT_UNDEF_ULONG, 1UL);
  gt_option_parser_add_option(op, num_option);


  coverage_option = gt_option_new_ulong_min("coverage",
                                            "desired coverage of the reads",
                                            &arguments->coverage,
                                            GT_UNDEF_ULONG, 1UL);
  gt_option_parser_add_option(op, coverage_option);


  len_option = gt_option_new_ulong_min("len", "fixed read length",
                                               &arguments->minlen,
                                               GT_UNDEF_ULONG, 1UL);
  gt_option_parser_add_option(op, len_option);


  minlen_option = gt_option_new_ulong_min("minlen",
                                          "minimal read length",
                                          &arguments->minlen,
                                          GT_UNDEF_ULONG, 1UL);
  gt_option_parser_add_option(op, minlen_option);


  maxlen_option = gt_option_new_ulong_min("maxlen",
                                          "maximal read length",
                                          &arguments->maxlen,
                                          GT_UNDEF_ULONG, 1UL);
  gt_option_parser_add_option(op, maxlen_option);


  distlen_option = gt_option_new_string("distlen",
      "use read length distribution file\n"
      "(in the output format of the seqstat tool)",
      arguments->distlen_filename, NULL);
  gt_option_parser_add_option(op, distlen_option);

  ;
  gt_output_file_register_options(op, &arguments->outfp, arguments->ofi);


  p_option = gt_option_new_bool("p", "show a progress bar",
                                &arguments->show_progressbar, false);
  gt_option_parser_add_option(op, p_option);


  v_option = gt_option_new_bool("v", "be verbose",
                                &arguments->verbose, false);
  gt_option_parser_add_option(op, v_option);


  ds_option = gt_option_new_string("ds", "output distribution of starting"
                                       " positions to specified file",
                                   arguments->dsfilename, NULL);
  gt_option_parser_add_option(op, ds_option);
  gt_option_is_extended_option(ds_option);


  dl_option = gt_option_new_string("dl", "output distribution of read lengths"
                                       " to specified file",
                                   arguments->dlfilename, NULL);
  gt_option_parser_add_option(op, dl_option);
  gt_option_is_extended_option(dl_option);


  ss_option = gt_option_new_bool("ss", "simulate reads in forward direction "
                                 "only", &arguments->singlestrand, false);
  gt_option_parser_add_option(op, ss_option);

  gt_option_is_mandatory_either(num_option, coverage_option);
  gt_option_is_mandatory_either_3(len_option, minlen_option, distlen_option);
  gt_option_imply(minlen_option, maxlen_option);
  gt_option_imply(maxlen_option, minlen_option);
  gt_option_exclude(maxlen_option, len_option);
  gt_option_exclude(maxlen_option, distlen_option);
  gt_option_exclude(minlen_option, len_option);
  gt_option_exclude(minlen_option, distlen_option);
  gt_option_exclude(len_option, distlen_option);
  gt_option_exclude(len_option, dl_option);

  gt_option_parser_set_min_max_args(op, 1U, 1U);

  gt_option_parser_set_mail_address(op,"<gonnella@zbh.uni-hamburg.de>");

  return op;
}

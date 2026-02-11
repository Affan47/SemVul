gt_index_options_register_generic_output(GtOptionParser *op,
                                         GtIndexOptions *idxo,
                                         GtStr *indexname,
                                         GtEncseqOptions *encopts)
{
  gt_assert(idxo != NULL);
  gt_assert(op != NULL && idxo->type != GT_INDEX_OPTIONS_UNDEFINED &&
            encopts != NULL);
  idxo->encopts = encopts;
  idxo->indexname = indexname != NULL ? gt_str_ref(indexname) : NULL;
  idxo->optionkys = gt_option_new_string("kys",
                                   "output/sort according to keys of the form "
                                   "|key| in fasta header",
                                   idxo->kysargumentstring,
                                   "nosort");
  gt_option_argument_is_optional(idxo->optionkys);
  gt_option_imply(idxo->optionkys, gt_encseq_options_sds_option(idxo->encopts));
  gt_option_parser_add_option(op, idxo->optionkys);

  gt_encseq_options_add_readmode_option(op, idxo->dir);

  if (idxo->type == GT_INDEX_OPTIONS_ESA)
  {
    idxo->optionoutsuftab = gt_option_new_bool("suf",
                                   "output suffix array (suftab) to file",
                                   &idxo->outsuftab,
                                   false);
    gt_option_parser_add_option(op, idxo->optionoutsuftab);

    idxo->optionoutlcptab = gt_option_new_bool("lcp",
                                   "output lcp table (lcptab) to file",
                                   &idxo->outlcptab,
                                   false);
    gt_option_parser_add_option(op, idxo->optionoutlcptab);

    idxo->option = gt_option_new_bool("lcpdist",
                              "output distributions of values in lcptab",
                              &idxo->lcpdist,
                              false);
    gt_option_is_extended_option(idxo->option);
    gt_option_imply(idxo->option, idxo->optionoutlcptab);
    gt_option_parser_add_option(op, idxo->option);

    idxo->option = gt_option_new_bool("swallow-tail",
                              "swallow the tail of the suffix array and lcptab",
                              &idxo->swallow_tail,
                              false);
    gt_option_is_development_option(idxo->option);
    gt_option_parser_add_option(op, idxo->option);

    idxo->optionoutbwttab = gt_option_new_bool("bwt",
                                   "output Burrows-Wheeler Transformation "
                                   "(bwttab) to file",
                                   &idxo->outbwttab,
                                   false);
    gt_option_exclude(idxo->optionspmopt, idxo->optionoutbwttab);
    gt_option_parser_add_option(op, idxo->optionoutbwttab);

    idxo->optionoutbcktab = gt_option_new_bool("bck",
                                "output bucket table to file",
                                &idxo->outbcktab,
                                false);
    gt_option_parser_add_option(op, idxo->optionoutbcktab);
  } else {
    idxo->optionoutsuftab
      = idxo->optionoutlcptab = idxo->optionoutbwttab = NULL;
    idxo->sfxstrategy.spmopt_minlength = 0;
#ifndef S_SPLINT_S
    gt_registerPackedIndexOptions(op,
                                  &idxo->bwtIdxParams,
                                  BWTDEFOPT_CONSTRUCTION,
                                  idxo->indexname);
#endif
  }

  gt_option_parser_register_hook(op, gt_index_options_check_set_out_opts, idxo);

  return idxo;
}

gt_shredder_runner(GT_UNUSED int argc, const char **argv,
                              int parsed_args, void *tool_arguments,
                              GtError *err)
{
  ShredderArguments *arguments = tool_arguments;
  GtBioseqIterator *bsi;
  unsigned long i;
  GtBioseq *bioseq;
  int had_err;
  GtStr *desc;

  gt_error_check(err);
  gt_assert(arguments);


  desc = gt_str_new();
  bsi = gt_bioseq_iterator_new(argc - parsed_args, argv + parsed_args);


  while (!(had_err = gt_bioseq_iterator_next(bsi, &bioseq, err)) && bioseq) {
    for (i = 0; i < arguments->coverage; i++) {
      GtShredder *shredder;
      unsigned long fragment_length;
      char *fragment;
      shredder = gt_shredder_new(bioseq, arguments->minlength,
                              arguments->maxlength);
      gt_shredder_set_overlap(shredder, arguments->overlap);
      gt_shredder_set_sample_probability(shredder,
                                         arguments->sample_probability);
      while ((fragment = gt_shredder_shred(shredder, &fragment_length, desc))) {
        gt_str_append_cstr(desc, " [shreddered fragment]");
        gt_fasta_show_entry(gt_str_get(desc), fragment, fragment_length,
                            arguments->width, arguments->outfp);
        gt_free(fragment);
      }
      gt_shredder_delete(shredder);
    }
    gt_bioseq_delete(bioseq);
  }


  gt_bioseq_iterator_delete(bsi);
  gt_str_delete(desc);

  return had_err;
}

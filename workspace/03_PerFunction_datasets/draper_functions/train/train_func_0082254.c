gt_magicmatch_runner(GT_UNUSED int argc, GT_UNUSED const char **argv,
                                GT_UNUSED int parsed_args, void *tool_arguments,
                                GtError *err)
{
  MagicMatchArguments *arguments = tool_arguments;
  GtBioseq *bioseq;
  unsigned long i;
  int had_err = 0;

  gt_error_check(err);
  gt_assert(arguments);

  if (arguments->translate) {
    for (i = 0; !had_err && i < gt_str_array_size(arguments->seqfiles); i++) {
      if (!(bioseq = gt_bioseq_new(gt_str_array_get(arguments->seqfiles, i),
                                   err))) {
        had_err = -1;
      }
      if (!had_err)
        translate_sequence_file(bioseq);
      gt_bioseq_delete(bioseq);
    }
  }

  return had_err;
}

gt_seq_arguments_check(int rest_argc, void *tool_arguments,
                                  GtError *err)
{
  SeqArguments *arguments = tool_arguments;
  gt_error_check(err);
  gt_assert(arguments);

  if (arguments->showseqnum != GT_UNDEF_ULONG && rest_argc > 1) {
    gt_error_set(err, "option '-showseqnum' makes only sense with a single "
                      "sequence_file");
    return -1;
  }
  return 0;
}

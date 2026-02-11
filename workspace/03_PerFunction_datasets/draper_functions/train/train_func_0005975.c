gt_encseq_options_add_readmode_option(GtOptionParser *op, GtStr *readmode)
{
  GtOption *optiondir;
  gt_assert(op && readmode);
  optiondir = gt_option_new_string("dir", "specify reading direction "
                                          "(fwd, cpl, rev, rcl)",
                                   readmode, "fwd");
  gt_option_parser_add_option(op, optiondir);
}

gt_strgraph_load_spm_from_file(GtStrgraph *strgraph,
    unsigned long min_length, bool load_self_spm, GtBitsequence *contained,
    const char *indexname, unsigned int nspmfiles, const char *suffix,
    GtError *err)
{
  int had_err = 0;
  GtStr *filename = gt_str_new();
  GtSpmprocSkipData skipdata;
  unsigned int i;

  gt_assert(strgraph != NULL);
  if (contained != NULL)
  {
    skipdata.out.e.proc = gt_spmproc_strgraph_add;
    skipdata.to_skip = contained;
    skipdata.out.e.data = strgraph;
  }
  strgraph->load_self_spm = load_self_spm;
  for (i = 0; i < nspmfiles; i++)
  {
    gt_str_append_cstr(filename, indexname);
    gt_str_append_char(filename, '.');
    gt_str_append_uint(filename, i);
    gt_str_append_cstr(filename, suffix);
    had_err = gt_spmlist_parse(gt_str_get(filename), min_length,
        contained != NULL ? gt_spmproc_skip : gt_spmproc_strgraph_add,
        contained != NULL ? (void*)&skipdata : (void*)strgraph, err);
    gt_str_reset(filename);
  }
  gt_str_delete(filename);
  if (!had_err)
    gt_strgraph_mark_empty_edges(strgraph);
  return had_err;
}

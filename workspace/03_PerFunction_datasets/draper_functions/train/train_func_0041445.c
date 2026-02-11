gt_seqcorrect_apply_corrections(GtEncseq *encseq,
    const char *indexname, const unsigned int threads,
    GtError *err)
{
  bool haserr = false;
  GtTwobitencEditor *editor;
  unsigned int threadcount;
  editor = gt_twobitenc_editor_new(encseq, indexname, err);
  if (editor == NULL)
    haserr = true;
  gt_log_log("number of correction lists: %u", threads);
  for (threadcount = 0; !haserr && threadcount < threads; threadcount++)
  {
    FILE *corrections;
    GtStr *filename;
    filename = gt_str_new_cstr(indexname);
    gt_str_append_char(filename, '.');
    gt_str_append_uint(filename, threadcount);
    gt_str_append_cstr(filename, GT_SEQCORRECT_FILESUFFIX);
    corrections = gt_fa_fopen(gt_str_get(filename), "r", err);
    gt_log_log("apply corrections list %s.%u.%s", indexname, threadcount,
        GT_SEQCORRECT_FILESUFFIX);
    if (corrections == NULL)
      haserr = true;
    else
    {
      unsigned long pos;
      GtUchar newchar;
      size_t retval;
      while ((retval = fread(&pos, sizeof (pos), (size_t)1, corrections))
          == (size_t)1)
      {
        newchar = (GtUchar)(pos & 3UL);
        pos >>= 2;
        gt_twobitenc_editor_edit(editor, pos, newchar);
      }
      if (ferror(corrections) != 0)
      {
        gt_error_set(err, "error by reading file %s", gt_str_get(filename));
        haserr = true;
      }
      gt_fa_fclose(corrections);
    }
    gt_str_delete(filename);
  }
  gt_twobitenc_editor_delete(editor);
  return haserr ? -1 : 0;
}

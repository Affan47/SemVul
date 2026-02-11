gt_file_size_with_suffix(const char *path, const char *suffix)
{
  GtStr *tmpfilename;
  off_t tmpsize;

  gt_assert(path && suffix);

  tmpfilename = gt_str_new_cstr(path);
  gt_str_append_cstr(tmpfilename, suffix);
  tmpsize = gt_file_size(gt_str_get(tmpfilename));
  gt_str_delete(tmpfilename);
  return tmpsize;
}

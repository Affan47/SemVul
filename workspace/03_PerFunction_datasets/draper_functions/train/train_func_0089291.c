gt_file_xopen(const char *path, const char *mode)
{
  gt_assert(mode);
  return gt_file_xopen_file_mode(gt_file_mode_determine(path), path, mode);
}

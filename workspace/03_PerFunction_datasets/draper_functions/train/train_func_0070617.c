gt_str_array_new_file(const char *path)
{
  GtStrArray *filecontent;
  GtFile *fpin;
  GtStr *line;
  fpin = gt_file_xopen(path, "r");
  gt_assert(fpin);
  line = gt_str_new();
  filecontent = gt_str_array_new();
  while (gt_str_read_next_line_generic(line, fpin) != EOF) {
    gt_str_array_add_cstr(filecontent, gt_str_get(line));
    gt_str_reset(line);
  }
  gt_str_delete(line);
  gt_file_delete(fpin);
  return filecontent;
}

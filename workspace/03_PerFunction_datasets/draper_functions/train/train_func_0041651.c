gt_simreads_write_dist_file(const char *title, GtDiscDistri *dist,
                                       GtStr *filename, GtError *err)
{
  int had_err = 0;
  GtFile *dfile;

  gt_assert(filename);
  gt_assert(dist);
  gt_error_check(err);
  dfile = gt_file_new(gt_str_get(filename), "w", err);
  if (!dfile)
  {
    had_err = -1;
  }
  else
  {
    gt_file_xprintf(dfile, "%s", title);
    gt_disc_distri_foreach(dist,
     (GtDiscDistriIterFunc) gt_simreads_plot_disc_distri, dfile);
    gt_file_delete(dfile);
  }
  return had_err;
}

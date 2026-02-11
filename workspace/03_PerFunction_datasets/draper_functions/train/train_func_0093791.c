get_obo_path(GtError *err)
{
  const char *progname;
  GtStr *obo_path, *prog;
  gt_error_check(err);
  progname = gt_error_get_progname(err);
  gt_assert(progname != NULL);
  prog = gt_str_new();
  gt_str_append_cstr_nt(prog, progname,
                        gt_cstr_length_up_to_char(progname, ' '));
  obo_path = gt_get_gtdata_path(gt_str_get(prog), err);
  if (obo_path)
    gt_str_append_cstr(obo_path, "/obo_files/");
  gt_str_delete(prog);
  return obo_path;
}

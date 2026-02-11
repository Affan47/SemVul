waypt_write_cb(GPS_PWay* way)
{
  static int i;
  int n = waypt_count();

  if (global_opts.verbose_status) {
    i++;
    waypt_status_disp(n, i);
  }
  return 0;
}

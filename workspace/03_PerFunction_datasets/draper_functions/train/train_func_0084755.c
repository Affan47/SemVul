gdb_wr_init(const char* fname)
{
  fout = gbfopen_le(fname, "wb", MYNAME);
  ftmp = gbfopen_le(NULL, "wb", MYNAME);

  gdb_category = (gdb_opt_category) ? atoi(gdb_opt_category) : 0;
  gdb_ver = (gdb_opt_ver && *gdb_opt_ver) ? atoi(gdb_opt_ver) : 0;

  if (gdb_category) {
    is_fatal((gdb_category < 1) || (gdb_category > 16),
             MYNAME ": cat must be between 1 and 16!");
    gdb_category = 1 << (gdb_category - 1);
  }

  if (gdb_opt_bitcategory) {
    gdb_category = strtol(gdb_opt_bitcategory, NULL, 0);
  }

  if (gdb_ver >= GDB_VER_UTF8) {
    cet_convert_init(CET_CHARSET_UTF8, 1);
  }

  QUEUE_INIT(&wayptq_out);
  short_h = NULL;

  waypt_ct = 0;
  waypth_ct = 0;
  rtept_ct = 0;
  trkpt_ct = 0;
  rte_ct = 0;
  trk_ct = 0;
}

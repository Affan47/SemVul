maggeo_wr_init(const char* fname)
{
  if (waypt_count() > 200) {
    fatal(MYNAME ": eXplorist does not support more than 200 waypoints in one .gs file.\nDecrease the number of waypoints sent.\n");
  }
  maggeofile_out = gbfopen(fname, "wb", MYNAME);
  desc_handle = mkshort_new_handle();
  setshort_length(desc_handle, 20);
  setshort_badchars(desc_handle, "\"$,");
}

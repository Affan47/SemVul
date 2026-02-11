gtm_rd_init(const char* fname)
{
  int version;
  char* name;
  file_in = gbfopen_le(fname, "rb", MYNAME);
  version = fread_integer(file_in);
  name = fread_fixedstring(file_in, 10);
  if (version == -29921) {
    fatal(MYNAME ": Uncompress the file first\n");
  }
  if (strcmp(name, "TrackMaker") != 0) {
    fatal(MYNAME ": Invalid file format\n");
  }
  if (version != 211) {
    fatal(MYNAME ": Invalid format version\n");
  }
  xfree(name);


  fread_discard(file_in, 15);
  ws_count = fread_long(file_in);
  fread_discard(file_in, 4);
  wp_count = fread_long(file_in);
  tr_count = fread_long(file_in);
  rt_count = fread_long(file_in);
  fread_discard(file_in, 16);
  im_count = fread_long(file_in);
  ts_count = fread_long(file_in);
  fread_discard(file_in, 28);
  fread_string_discard(file_in);
  fread_string_discard(file_in);
  fread_string_discard(file_in);
  fread_string_discard(file_in);


  fread_discard(file_in, 34);
  set_datum(fread_integer(file_in));
  fread_discard(file_in, 22);
}

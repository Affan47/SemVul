data_read(void)
{
  if ((file_in->creator != MYCREATOR) || ((file_in->type != MYTYPETRACK) && (file_in->type != MYTYPEWPT))) {
    warning("Creator %x Type %x Version %d\n", (int) file_in->creator, (int) file_in->type, (int) file_in->version);
    fatal(MYNAME ": Not a cotoGPS file.\n");
  }

  is_fatal((file_in->version > 0),
           MYNAME ": This file is from an unsupported newer version of cotoGPS.  It may be supported in a newer version of GPSBabel.\n");

  switch (file_in->type) {
  case MYTYPETRACK:
    coto_track_read();
    break;
  case MYTYPEWPT:
    coto_wpt_read();
    break;
  }
}

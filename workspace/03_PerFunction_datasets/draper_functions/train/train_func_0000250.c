artec48u_scanner_stop_scan (Artec48U_Scanner * s)
{
  XDBG ((1, "artec48u_scanner_stop_scan begin: \n"));
  artec48u_line_reader_free (s->reader);
  s->reader = NULL;

  return artec48u_stop_scan (s->dev);
}

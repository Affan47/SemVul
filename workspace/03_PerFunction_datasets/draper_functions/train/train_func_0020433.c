data_read(void)
{
  char *buff;
  int linecount = 0;
  while ((buff = gbfgetstr(file_in))) {
    char *s;
    waypoint *wpt;
    rtrim(buff);
    if (strlen(buff) == 0) {
      break;
    }
    linecount++;
    wpt = waypt_new();
    s = buff;
    s = csv_lineparse(s, "\\w", "", linecount);
    wpt->shortname = xstrdup(s);
    s = csv_lineparse(NULL, "\\w", "", linecount);
    wpt->latitude = wppos_to_dec(s);
    s = csv_lineparse(NULL, "\\w", "", linecount);
    wpt->longitude = wppos_to_dec(s);
    waypt_add(wpt);
  }
}

unix_to_sfbin_date_string(long gmt)
{

  static char buf[9];
  unsigned short s_time, s_date;

  date_unix2dos(((gmt == -1) ? time(0) : gmt), &s_time, &s_date);
  sprintf(buf, "%X", ((s_date << 16) + s_time));
  return buf;
}

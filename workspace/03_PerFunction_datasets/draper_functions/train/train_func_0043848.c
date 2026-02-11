build_time(char *smonth, int day, int hour, int minute, int second)
{
  int month = 0, now, then;
  struct tm *t;

  if (opt.mode != REALTIME_RESPONSE) {
    t = localtime(&opt.now);
  } else {
    time_t rr_now;

    rr_now = time(NULL);
    t = localtime(&rr_now);
  }
  now = (int) mktime(t);
  if (strncmp(smonth, "Jan", 3) == 0) {
    month = 0;
  } else if (strncmp(smonth, "Feb", 3) == 0) {
    month = 1;
  } else if (strncmp(smonth, "Mar", 3) == 0) {
    month = 2;
  } else if (strncmp(smonth, "Apr", 3) == 0) {
    month = 3;
  } else if (strncmp(smonth, "May", 3) == 0) {
    month = 4;
  } else if (strncmp(smonth, "Jun", 3) == 0) {
    month = 5;
  } else if (strncmp(smonth, "Jul", 3) == 0) {
    month = 6;
  } else if (strncmp(smonth, "Aug", 3) == 0) {
    month = 7;
  } else if (strncmp(smonth, "Sep", 3) == 0) {
    month = 8;
  } else if (strncmp(smonth, "Oct", 3) == 0) {
    month = 9;
  } else if (strncmp(smonth, "Nov", 3) == 0) {
    month = 10;
  } else if (strncmp(smonth, "Dec", 3) == 0) {
    month = 11;
  }
  t->tm_mon = month;
  t->tm_mday = day;
  t->tm_hour = hour;
  t->tm_min = minute;
  t->tm_sec = second;
  t->tm_isdst = -1;
  then = (int) mktime(t);
  if (then > now)
    --t->tm_year;

  opt.line->time = mktime(t);
}

read_iso8601_time(char *linepos, logdata *data) {
  struct tm tm;
  tm.tm_sec = 0;
  tm.tm_min = 0;
  tm.tm_hour = 0;
  tm.tm_mday = 0;
  tm.tm_mon = 0;
  tm.tm_year = 0;
  tm.tm_wday = 0;
  tm.tm_isdst = -1;

  char *line = strptime(linepos, "%Y-%m-%d %T", &tm);
  if (line == NULL) return NULL;


  if (*line == '.') {
    line++;
    while(isdigit(*line)) {
      line++;
    }
  }
  data->date = mktime(&tm);

  return line;
}
